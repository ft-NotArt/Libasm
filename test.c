#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

size_t ft_strlen(char *str) ;
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);

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
		printf("\t strcpy: error on empty strings \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "") ;
	bzero(str2, 100) ;	strcpy(str2, "++") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcpy: error on empty string (first one) \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "++") ;
	bzero(str2, 100) ;	strcpy(str2, "") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcpy: error on empty string (second one) \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "++") ;
	bzero(str2, 100) ;	strcpy(str2, "++") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcpy: error on same strings \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "++++") ;
	bzero(str2, 100) ;	strcpy(str2, "++") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcpy: error on similar strings (not same length) \n") ;
		res = false ;
	}

	bzero(str1, 100) ;	strcpy(str1, "++") ;
	bzero(str2, 100) ;	strcpy(str2, "--") ;
	if (strcmp(str1, str2) != ft_strcmp(str1, str2)) {
		printf("\t strcpy: error on different strings \n") ;
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
		printf("\t strcpy: error on empty string \n") ;
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
		printf("\t strcpy: error on classic string \n") ;
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
		printf("\t strcpy: error on classic string \n") ;
		res = false ;
	}
	close(write_fd) ; close(read_fd) ;


	bzero(real_read_str, 100) ; bzero(ft_read_str, 100) ; bzero(write_str, 100) ; strcpy(write_str, "wrong fd !") ;

	real_retVal = write(-2, write_str, strlen(write_str)) ;
	real_errnoVal = errno ;

	ft_retVal = ft_write(-2, write_str, strlen(write_str)) ;
	ft_errnoVal = errno ;
	
	if (real_retVal != ft_retVal || real_errnoVal != ft_errnoVal) {
		printf("\t strcpy: error on classic string \n") ;
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
		printf("\t strcpy: error on classic string \n") ;
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
		printf("\t strcpy: error on empty string \n") ;
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
		printf("\t strcpy: error on classic string \n") ;
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
		printf("\t strcpy: error on classic string \n") ;
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
		printf("\t strcpy: error on classic string \n") ;
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
		printf("\t strcpy: error on classic string \n") ;
		res = false ;
	}


	return res ;
}

int main(int argc, char *argv[]) {
	printf("/===========================\\\n");
	printf("|   LET'S BEGIN THE TESTS   |\n");
	printf("\\===========================/\n");
	printf("\n\n") ;

	printf("strlen : %s \n", test_strlen() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("strcpy : %s \n", test_strcpy() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("strcmp : %s \n", test_strcmp() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("write : %s \n", test_write() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("read : %s \n", test_read() ? "👑" : "🖕") ;
	printf("\n\n") ;
}