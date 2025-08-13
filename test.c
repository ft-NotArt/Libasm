#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <strings.h>

size_t ft_strlen(char *str) ;
char *ft_strcpy(char *dest, const char *src);

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

int main(int argc, char *argv[]) {
	printf("/===========================\\\n");
	printf("|   LET'S BEGIN THE TESTS   |\n");
	printf("\\===========================/\n");
	printf("\n\n") ;

	printf("strlen : %s \n", test_strlen() ? "👑" : "🖕") ;
	printf("\n\n") ;

	printf("strcpy : %s \n", test_strcpy() ? "👑" : "🖕") ;
	printf("\n\n") ;
}