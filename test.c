#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <string.h>
#include <strings.h>

#include <fcntl.h>
#include <dlfcn.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


typedef struct s_list {
	void *data ;
	struct s_list *next ;
} t_list ;


size_t ft_strlen(char *str) ;
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);
int ft_atoi_base(char *str, char *base);
void ft_list_push_front(t_list **begin_list, void *data);
int ft_list_size(t_list *begin_list);
void ft_list_sort(t_list **begin_list, int (*cmp)(void *, void *));
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));


/* Utilitary Linked List Functions */

void free_list(t_list **head) {
	t_list *cur, *next ;

	cur = *head ;
	while (cur) {
		next = cur->next ;
		free(cur) ;
		cur = next ;
	}
}

int cmp_int_sortAscending(void *data, void *other_data) {
	int a = *(int *)data;
	int b = *(int *)other_data;
	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}

int cmp_int_sortDescending(void *data, void *other_data) {
	int a = *(int *)data;
	int b = *(int *)other_data;
	if (a < b) return 1;
	if (a > b) return -1;
	return 0;
}

int cmpstr(void *data, void *other_data) { // Just to avoid annoying compilation warnings
	return (strcmp(data, other_data)) ;
}

int cmp_int_isEqual(void *data, void *other_data) {
	int a = *(int *)data;
	int b = *(int *)other_data;
	if (a == b) return 0;
	return 1;
}

void do_nothing(void *data) {
	(void) data ;
	return ;
}


bool test_strlen() {
	char str[100] ;
	bool res = true ;

	bzero(str, 100) ; strcpy(str, "") ;
	if (strlen(str) != ft_strlen(str)) {
		printf("\t strlen: error on empty string \n") ;
		res = false ;
	}
	
	bzero(str, 100) ; strcpy(str, "test") ;
	if (strlen(str) != ft_strlen(str)) {
		printf("\t strlen: error on little string \n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttestt") ;
	if (strlen(str) != ft_strlen(str)) {
		printf("\t strlen: error on big string \n") ;
		res = false ;
	}

	return res ;
}

bool test_strcpy() {
	char dest[100] ;
	char src[100] ;
	bool res = true ;

	bzero(dest, 100) ; bzero(src, 100) ; strcpy(src, "") ;
	if (ft_strcpy(dest, src) != dest || strcmp(dest, src)) {
		printf("\t strcpy: error on empty string \n") ;
		res = false ;
	}
	
	bzero(dest, 100) ; bzero(src, 100) ; strcpy(src, "test") ;
	if (ft_strcpy(dest, src) != dest || strcmp(dest, src)) {
		printf("\t strcpy: error on little string \n") ;
		res = false ;
	}

	bzero(dest, 100) ; bzero(src, 100) ; strcpy(src, "testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttestt") ;
	if (ft_strcpy(dest, src) != dest || strcmp(dest, src)) {
		printf("\t strcpy: error on big string \n") ;
		res = false ;
	}

	return res ;
}

bool test_strcmp() {
	char str1[100] ;
	char str2[100] ;
	bool res = true ;

	bzero(str1, 100) ;	strcpy(str1, "") ;
	bzero(str2, 100) ;	strcpy(str2, "") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcmp: error on empty strings \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "") ;
	bzero(str2, 100) ;	strcpy(str2, "++") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcmp: error on empty string (first one) \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "++") ;
	bzero(str2, 100) ;	strcpy(str2, "") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcmp: error on empty string (second one) \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "++") ;
	bzero(str2, 100) ;	strcpy(str2, "++") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcmp: error on same strings \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "++++") ;
	bzero(str2, 100) ;	strcpy(str2, "++") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcmp: error on similar strings (not same length) \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "++") ;
	bzero(str2, 100) ;	strcpy(str2, "--") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcmp: error on different strings \n") ;
		res = false ;
	}

	return res ;
}

bool test_write() {
	char write_str[100] ;
	char real_read_str[100] ;
	char ft_read_str[100] ;
	bool res = true ;

	int write_fd, read_fd ;
	int real_retVal, ft_retVal, real_errnoVal, ft_errnoVal ;


	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "") ;

	write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	real_retVal = write(write_fd, write_str, strlen(write_str)) ;
	real_errnoVal = errno ;
	read(read_fd, real_read_str, 100) ;

	close(write_fd) ; write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	close(read_fd) ; read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	ft_retVal = ft_write(write_fd, write_str, strlen(write_str)) ;
	ft_errnoVal = errno ;
	read(read_fd, ft_read_str, 100) ;
	
	if (strcmp(real_read_str, ft_read_str) || real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t write: error on empty string \n") ;
		res = false ;
	}
	close(write_fd) ; close(read_fd) ;


	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "bonjour!") ;

	write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	real_retVal = write(write_fd, write_str, strlen(write_str)) ;
	real_errnoVal = errno ;
	read(read_fd, real_read_str, 100) ;

	close(write_fd) ; write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	close(read_fd) ; read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	ft_retVal = ft_write(write_fd, write_str, strlen(write_str)) ;
	ft_errnoVal = errno ;
	read(read_fd, ft_read_str, 100) ;

	if (strcmp(real_read_str, ft_read_str) || real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t write: error on classic string \n") ;
		res = false ;
	}
	close(write_fd) ; close(read_fd) ;


	write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "wrong size !") ;

	real_retVal = write(write_fd, write_str, strlen(write_str) - 5) ;
	real_errnoVal = errno ;
	read(read_fd, real_read_str, 100) ;

	close(write_fd) ; write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	close(read_fd) ; read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	ft_retVal = ft_write(write_fd, write_str, strlen(write_str) - 5) ;
	ft_errnoVal = errno ;
	read(read_fd, ft_read_str, 100) ;
	
	if (strcmp(real_read_str, ft_read_str) || real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t write: error on classic string \n") ;
		res = false ;
	}
	close(write_fd) ; close(read_fd) ;


	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "wrong fd !") ;

	real_retVal = write(-2, write_str, strlen(write_str)) ;
	real_errnoVal = errno ;

	ft_retVal = ft_write(-2, write_str, strlen(write_str)) ;
	ft_errnoVal = errno ;
	
	if (real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t write: error on classic string \n") ;
		res = false ;
	}


	read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "wrong fd again !") ;

	real_retVal = write(read_fd, write_str, strlen(write_str)) ;
	real_errnoVal = errno ;

	close(read_fd) ; read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	ft_retVal = ft_write(read_fd, write_str, strlen(write_str)) ;
	ft_errnoVal = errno ;
	
	if (real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t write: error on classic string \n") ;
		res = false ;
	}
	close(read_fd) ;


	return res ;
}

bool test_read() {
	char write_str[100] ;
	char real_read_str[100] ;
	char ft_read_str[100] ;
	bool res = true ;

	int write_fd, read_fd ;
	int real_retVal, ft_retVal, real_errnoVal, ft_errnoVal ;


	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "") ;

	write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	write(write_fd, write_str, strlen(write_str)) ;
	
	real_retVal = read(read_fd, real_read_str, 100) ;
	real_errnoVal = errno ;
	close(read_fd) ; read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	ft_retVal = ft_read(read_fd, ft_read_str, 100) ;
	ft_errnoVal = errno ;
	
	if (strcmp(real_read_str, ft_read_str) || real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t read: error on empty string \n") ;
		res = false ;
	}
	close(write_fd) ; close(read_fd) ;


	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "bonjour!") ;

	write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	write(write_fd, write_str, strlen(write_str)) ;
	
	real_retVal = read(read_fd, real_read_str, 100) ;
	real_errnoVal = errno ;
	close(read_fd) ; read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	ft_retVal = read(read_fd, ft_read_str, 100) ;
	ft_errnoVal = errno ;

	if (strcmp(real_read_str, ft_read_str) || real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t read: error on classic string \n") ;
		res = false ;
	}
	close(write_fd) ; close(read_fd) ;


	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "wrong size !") ;

	write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	write(write_fd, write_str, strlen(write_str)) ;
	
	real_retVal = read(read_fd, real_read_str, strlen(write_str) - 5) ;
	real_errnoVal = errno ;
	close(read_fd) ; read_fd = open("test.txt", O_RDONLY | O_CREAT, 0777) ;
	ft_retVal = read(read_fd, ft_read_str, strlen(write_str) - 5) ;
	ft_errnoVal = errno ;
	
	if (strcmp(real_read_str, ft_read_str) || real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t read: error on classic string \n") ;
		res = false ;
	}
	close(write_fd) ; close(read_fd) ;


	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "wrong fd !") ;

	write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	write(write_fd, write_str, strlen(write_str)) ;
	close(write_fd) ;

	real_retVal = read(-2, real_read_str, strlen(write_str)) ;
	real_errnoVal = errno ;
	ft_retVal = ft_read(-2, ft_read_str, strlen(write_str)) ;
	ft_errnoVal = errno ;
	
	if (real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t read: error on classic string \n") ;
		res = false ;
	}


	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "wrong fd again !") ;

	write_fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0777) ;
	write(write_fd, write_str, strlen(write_str)) ;
	close(write_fd) ;

	real_retVal = read(write_fd, real_read_str, strlen(write_str)) ;
	real_errnoVal = errno ;
	ft_retVal = ft_read(write_fd, ft_read_str, strlen(write_str)) ;
	ft_errnoVal = errno ;
	
	if (real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t read: error on classic string \n") ;
		res = false ;
	}


	return res ;
}


bool test_strdup() {
	char str[100] ;
	bool res = true ;

	char *real_ptr, *ft_ptr ;
	int real_errnoVal, ft_errnoVal ;


	bzero(str, 100) ; strcpy(str, "") ;

	real_ptr = strdup(str) ;
	real_errnoVal = errno ;

	ft_ptr = ft_strdup(str) ;
	ft_errnoVal = errno ;
	
	if (strcmp(real_ptr, ft_ptr) || real_errnoVal != ft_errnoVal) {
		printf("\t strdup: error on empty string \n") ;
		res = false ;
	}


	bzero(str, 100) ; strcpy(str, "bonjour !") ;

	real_ptr = strdup(str) ;
	real_errnoVal = errno ;

	ft_ptr = ft_strdup(str) ;
	ft_errnoVal = errno ;
	
	if (strcmp(real_ptr, ft_ptr) || real_errnoVal != ft_errnoVal) {
		printf("\t strdup: error on classic string \n") ;
		res = false ;
	}


	bzero(str, 100) ; strcpy(str, "testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttestt") ;

	real_ptr = strdup(str) ;
	real_errnoVal = errno ;

	ft_ptr = ft_strdup(str) ;
	ft_errnoVal = errno ;
	
	if (strcmp(real_ptr, ft_ptr) || real_errnoVal != ft_errnoVal) {
		printf("\t strdup: error on big string \n") ;
		res = false ;
	}


	return res ;
}


bool test_atoi_base() {
	char str[100] ;
	char base[100] ;
	bool res = true ;


	bzero(str, 100) ; strcpy(str, "") ;
	bzero(base, 100) ; strcpy(base, "0123456789") ;
	if (ft_atoi_base(str, base) != 0) {
		printf("\t atoi_base: error on empty string\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "123") ;
	bzero(base, 100) ; strcpy(base, "") ;
	if (ft_atoi_base(str, base) != 0) {
		printf("\t atoi_base: error on empty base\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "123") ;
	bzero(base, 100) ; strcpy(base, "011233") ;
	if (ft_atoi_base(str, base) != 0) {
		printf("\t atoi_base: error on base w/ dupes\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "123") ;
	bzero(base, 100) ; strcpy(base, "123+") ;
	if (ft_atoi_base(str, base) != 0) {
		printf("\t atoi_base: error on base w/ invalid chars ('+' / '-' / ' ')\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "123") ;
	bzero(base, 100) ; strcpy(base, "1-23") ;
	if (ft_atoi_base(str, base) != 0) {
		printf("\t atoi_base: error on base w/ invalid chars ('+' / '-' / ' ')\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "123") ;
	bzero(base, 100) ; strcpy(base, "12 3") ;
	if (ft_atoi_base(str, base) != 0) {
		printf("\t atoi_base: error on base w/ invalid chars ('+' / '-' / ' ')\n") ;
		res = false ;
	}


	bzero(str, 100) ; strcpy(str, "446846486") ;
	bzero(base, 100) ; strcpy(base, "0123456789") ;
	if (ft_atoi_base(str, base) != 446846486) {
		printf("\t atoi_base: error on base 10\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "-2147483648") ;
	if (ft_atoi_base(str, base) != -2147483648) {
		printf("\t atoi_base: error on base 10, int min\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "2147483647") ;
	if (ft_atoi_base(str, base) != 2147483647) {
		printf("\t atoi_base: error on base 10, int max\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      446846486") ;
	if (ft_atoi_base(str, base) != 446846486) {
		printf("\t atoi_base: error on base 10, w/ spaces\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      +--+-+--+-+446846486") ;
	if (ft_atoi_base(str, base) != 446846486) {
		printf("\t atoi_base: error on base 10, w/ spaces & signs\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      +--+-+--+-+446846486ghgtuf") ;
	if (ft_atoi_base(str, base) != 446846486) {
		printf("\t atoi_base: error on base 10, /w spaces & signs & non-base characters after\n") ;
		res = false ;
	}


	bzero(str, 100) ; strcpy(str, "AAbBAbABb") ;
	bzero(base, 100) ; strcpy(base, "OIZEASbjBq") ;
	if (ft_atoi_base(str, base) != 446846486) {
		printf("\t atoi_base: error on base 10 (characters as numbers)\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      AAbBAbABb") ;
	if (ft_atoi_base(str, base) != 446846486) {
		printf("\t atoi_base: error on base 10 (characters as numbers), w/ spaces\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      +--+-+--+-+AAbBAbABb") ;
	if (ft_atoi_base(str, base) != 446846486) {
		printf("\t atoi_base: error on base 10 (characters as numbers), w/ spaces & signs\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      +--+-+--+-+AAbBAbABbghgtuf") ;
	if (ft_atoi_base(str, base) != 446846486) {
		printf("\t atoi_base: error on base 10 (characters as numbers), /w spaces & signs & non-base characters after\n") ;
		res = false ;
	}


	bzero(str, 100) ; strcpy(str, "OIIOIIO") ;
	bzero(base, 100) ; strcpy(base, "OI") ;
	if (ft_atoi_base(str, base) != 0b0110110) {
		printf("\t atoi_base: error on base 2 (characters as numbers)\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      OIIOIIO") ;
	if (ft_atoi_base(str, base) != 0b0110110) {
		printf("\t atoi_base: error on base 2 (characters as numbers), w/ spaces\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      +--+-+--+-+OIIOIIO") ;
	if (ft_atoi_base(str, base) != 0b0110110) {
		printf("\t atoi_base: error on base 2 (characters as numbers), w/ spaces & signs\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      +--+-+--+-+OIIOIIOghgtuf") ;
	if (ft_atoi_base(str, base) != 0b0110110) {
		printf("\t atoi_base: error on base 2 (characters as numbers), /w spaces & signs & non-base characters after\n") ;
		res = false ;
	}


	bzero(str, 100) ; strcpy(str, "ofe") ;
	bzero(base, 100) ; strcpy(base, "poneyvif") ;
	if (ft_atoi_base(str, base) != 0173) {
		printf("\t atoi_base: error on base 8 (characters as numbers)\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      ofe") ;
	if (ft_atoi_base(str, base) != 0173) {
		printf("\t atoi_base: error on base 8 (characters as numbers), w/ spaces\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      +--+-+--+-+ofe") ;
	if (ft_atoi_base(str, base) != 0173) {
		printf("\t atoi_base: error on base 8 (characters as numbers), w/ spaces & signs\n") ;
		res = false ;
	}

	bzero(str, 100) ; strcpy(str, "    \t \v \n \f      +--+-+--+-+ofeghgtuf") ;
	if (ft_atoi_base(str, base) != 0173) {
		printf("\t atoi_base: error on base 8 (characters as numbers), /w spaces & signs & non-base characters after\n") ;
		res = false ;
	}


	return res ;
}


bool test_list_push_front() {
	bool res = true ;

	t_list *node1, *node2, *node3 ;
	t_list **head ;
	int int0, int1, int2, int3 ;
	int i ;


	node1 = NULL ;
	int0 = 0 ;
	head = &node1 ;

	ft_list_push_front(head, &int0) ;
	i = 0 ;
	for (t_list *cur = *head; cur != NULL; cur = cur->next, i++) {
		if (*(int *)cur->data != i) {
			printf("\t list_push_front: error on empty linked list\n") ;
			res = false ;
		}
	}
	free_list(head) ;

	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	int0 = 0 ; int1 = 1 ; int2 = 2 ; int3 = 3 ;
	node1->data = &int1 ; node2->data = &int2 ; node3->data = &int3 ;
	head = &node1 ;

	ft_list_push_front(head, &int0) ;
	i = 0 ;
	for (t_list *cur = *head; cur != NULL; cur = cur->next, i++) {
		if (*(int *)cur->data != i) {
			printf("\t list_push_front: error on normal linked list\n") ;
			res = false ;
		}
	}
	free_list(head) ;


	return res ;
}


bool test_list_size() {
	bool res = true ;

	t_list *node1, *node2, *node3 ;
	t_list **head ;
	int int1, int2, int3 ;
	int i ;


	node1 = NULL ;
	head = &node1 ;

	if (ft_list_size(*head) != 0) {
		printf("\t list_size: error on empty linked list\n") ;
		res = false ;
	}

	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	int1 = 1 ; int2 = 2 ; int3 = 3 ;
	node1->data = &int1 ; node2->data = &int2 ; node3->data = &int3 ;
	head = &node1 ;

	if (ft_list_size(*head) != 3) {
		printf("\t list_size: error on normal linked list\n") ;
		res = false ;
	}
	free_list(head) ;


	return res ;
}


bool test_list_sort() {
	bool res = true ;

	t_list *node1, *node2, *node3 ;
	t_list **head ;
	int int1, int2, int3 ;
	char *str1, *str2, *str3 ;


	node1 = NULL ;
	head = &node1 ;
	ft_list_sort(head, cmp_int_sortAscending) ;


	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	int1 = 1 ; int2 = 2 ; int3 = 3 ;
	node1->data = &int1 ; node2->data = &int2 ; node3->data = &int3 ;
	head = &node1 ;

	ft_list_sort(head, cmp_int_sortAscending) ;
	for (t_list *cur = *head; cur != NULL && cur->next != NULL; cur = cur->next) {
		if (cmp_int_sortAscending(cur->data, cur->next->data) > 0) {
			printf("\t list_sort: error on int linked list, already sorted in ascending order\n") ;
			res = false ;
		}
	}
	free_list(head) ;

	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	int1 = 3 ; int2 = 1 ; int3 = 2 ;
	node1->data = &int1 ; node2->data = &int2 ; node3->data = &int3 ;
	head = &node1 ;

	ft_list_sort(head, cmp_int_sortAscending) ;
	for (t_list *cur = *head; cur != NULL && cur->next != NULL; cur = cur->next) {
		if (cmp_int_sortAscending(cur->data, cur->next->data) > 0) {
			printf("\t list_sort: error on int linked list, to be sorted in ascending order\n") ;
			res = false ;
		}
	}
	free_list(head) ;


	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	int1 = 3 ; int2 = 2 ; int3 = 1 ;
	node1->data = &int1 ; node2->data = &int2 ; node3->data = &int3 ;
	head = &node1 ;

	ft_list_sort(head, cmp_int_sortDescending) ;
	for (t_list *cur = *head; cur != NULL && cur->next != NULL; cur = cur->next) {
		if (cmp_int_sortDescending(cur->data, cur->next->data) > 0) {
			printf("\t list_sort: error on int linked list, already sorted in descending order\n") ;
			res = false ;
		}
	}
	free_list(head) ;

	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	int1 = 1 ; int2 = 3 ; int3 = 2 ;
	node1->data = &int1 ; node2->data = &int2 ; node3->data = &int3 ;
	head = &node1 ;

	ft_list_sort(head, cmp_int_sortDescending) ;
	for (t_list *cur = *head; cur != NULL && cur->next != NULL; cur = cur->next) {
		if (cmp_int_sortDescending(cur->data, cur->next->data) > 0) {
			printf("\t list_sort: error on int linked list, to be sorted in descending order\n") ;
			res = false ;
		}
	}
	free_list(head) ;


	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	str1 = strdup("a1") ; str2 = strdup("a2") ; str3 = strdup("a3") ;
	node1->data = str1 ; node2->data = str2 ; node3->data = str3 ;
	head = &node1 ;

	ft_list_sort(head, cmpstr) ;
	for (t_list *cur = *head; cur != NULL && cur->next != NULL; cur = cur->next) {
		if (cmpstr(cur->data, cur->next->data) > 0) {
			printf("\t list_sort: error on str linked list, already sorted in ascending order\n") ;
			res = false ;
		}
	}
	free_list(head) ; free(str1) ; free(str2) ; free(str3) ;

	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	str1 = strdup("a3") ; str2 = strdup("a2") ; str3 = strdup("a1") ;
	node1->data = str1 ; node2->data = str2 ; node3->data = str3 ;
	head = &node1 ;

	ft_list_sort(head, cmpstr) ;
	for (t_list *cur = *head; cur != NULL && cur->next != NULL; cur = cur->next) {
		if (cmpstr(cur->data, cur->next->data) > 0) {
			printf("\t list_sort: error on str linked list, already sorted in ascending order\n") ;
			res = false ;
		}
	}
	free_list(head) ; free(str1) ; free(str2) ; free(str3) ;


	return res ;
}


bool test_list_remove_if() {
	bool res = true ;

	t_list *node1, *node2, *node3 ;
	t_list **head ;
	int int1, int2, int3 ;
	char *str1, *str2, *str3, *str_ref ;


	node1 = NULL ;
	head = &node1 ;
	ft_list_remove_if(head, &int1, cmp_int_isEqual, do_nothing) ;


	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	int1 = 1 ; int2 = 2 ; int3 = 3 ;
	node1->data = &int1 ; node2->data = &int2 ; node3->data = &int3 ;
	head = &node1 ;

	ft_list_remove_if(head, &int1, cmp_int_isEqual, do_nothing) ;
	if (*(int *)((*head)->data) != 2 || *(int *)((*head)->next->data) != 3) {
		printf("\t list_remove_if: error on int linked list, remove on head\n") ;
		res = false ;
	}
	free_list(head) ;

	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	int1 = 1 ; int2 = 2 ; int3 = 3 ;
	node1->data = &int1 ; node2->data = &int2 ; node3->data = &int3 ;
	head = &node1 ;

	ft_list_remove_if(head, &int2, cmp_int_isEqual, do_nothing) ;
	if (*(int *)((*head)->data) != 1 || *(int *)((*head)->next->data) != 3) {
		printf("\t list_remove_if: error on int linked list, remove on middle\n") ;
		res = false ;
	}
	free_list(head) ;

	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	int1 = 1 ; int2 = 2 ; int3 = 3 ;
	node1->data = &int1 ; node2->data = &int2 ; node3->data = &int3 ;
	head = &node1 ;

	ft_list_remove_if(head, &int3, cmp_int_isEqual, do_nothing) ;
	if (*(int *)((*head)->data) != 1 || *(int *)((*head)->next->data) != 2) {
		printf("\t list_remove_if: error on int linked list, remove on end\n") ;
		res = false ;
	}
	free_list(head) ;


	node1 = malloc(sizeof(t_list)) ; node2 = malloc(sizeof(t_list)) ; node3 = malloc(sizeof(t_list)) ;
	node1->next = node2 ; node2->next = node3 ; node3->next = NULL ;
	str1 = strdup("a1") ; str2 = strdup("a2") ; str3 = strdup("a3") ; str_ref = strdup("a1") ;
	node1->data = str1 ; node2->data = str2 ; node3->data = str3 ;
	head = &node1 ;

	ft_list_remove_if(head, str_ref, strcmp, free) ;
	if (strcmp((*head)->data, str2) != 0 || strcmp((*head)->next->data, str3) != 0) {
		printf("\t list_remove_if: error on str linked list, remove on head\n") ;
		res = false ;
	}
	free_list(head) ; free(str2) ; free(str3) ; free(str_ref) ;


	return res ;
}


#define BEGIN_TESTS printf("/===========================\\\n|   LET'S BEGIN THE TESTS   |\n\\===========================/\n\n\n") ;

int main(int argc, char *argv[]) {

	if (argc > 1 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		printf("Options:\n") ;
		printf("\t -h, --help \t\t shows options\n") ;
		printf("\t -n, --no-bonus \t doesn't test bonus functions\n") ;
		printf("\t -i, --interactive \t ask for the name of a specific function to test\n") ;
		return 0 ;
	}

	if (argc > 1 && (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--interactive"))) {
		char input[250] ; bzero(input, 250) ;
		if (read(STDIN_FILENO, input, sizeof(input) - 1) == -1) {
			perror("read error") ;
			return 1 ;
		}

		char *newline = strchr(input, '\n') ;
		if (newline) *newline = '\0' ;

		char func_name[256] ;
		snprintf(func_name, sizeof(func_name), "test_%s", input) ;
		
		bool (*test_func)() = dlsym(NULL, func_name) ;

		printf("\n") ;

		if (dlerror() != NULL) {
			dprintf(STDERR_FILENO, "No function called %s to be tested\nPlease enter a function from the libasm when in interactive mode\n", input) ;
			return 1 ;
		} else {
			BEGIN_TESTS

			printf("%s : %s \n", input, test_func() ? "👑" : "🖕") ;
			printf("\n\n") ;

			return 0 ;
		}
	}


	BEGIN_TESTS

	printf("strlen : %s \n", test_strlen() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("strcpy : %s \n", test_strcpy() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("strcmp : %s \n", test_strcmp() ? "👑" : "🖕 (if run under valgrind, this one crashes because strcmp stops returning the diff between characters and only returns +/-1)") ;
	printf("\n\n") ;

	printf("write : %s \n", test_write() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("read : %s \n", test_read() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("strdup : %s \n", test_strdup() ? "👑" : "🖕") ;
	printf("\n\n") ;


	if (argc > 1 && (!strcmp(argv[1], "-n") || !strcmp(argv[1], "--no-bonus")))
		return 0 ;

	printf("atoi_base : %s \n", test_atoi_base() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("list_push_front : %s \n", test_list_push_front() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("list_size : %s \n", test_list_size() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("list_sort : %s \n", test_list_sort() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("list_remove_if : %s \n", test_list_remove_if() ? "👑" : "🖕") ;
	printf("\n\n") ;
}