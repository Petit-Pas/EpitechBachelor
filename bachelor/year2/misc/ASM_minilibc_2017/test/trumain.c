/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include <stdio.h>
#include <string.h>

char *_strstr(const char*, const char *);

int main()
{
	//const char buffer[] = "";
//        const char buffer2[] = "rghjk";
	int achieved = 0;
	int count = 0;


	count += 1;
        char *ptr1 = strstr("tarentino est pas ouf en vrai", "tarentino est pas ouf en vrai !");
	char *ptr2 = _strstr("tarentino est pas ouf en vrai", "tarentino est pas ouf en vrai !");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 1 passed\n", achieved++);
	else
		printf("\033[0;31mtest 1 failed\n");


	count += 1;
	ptr1 = strstr("tarentino est pas ouf en vrai", "banane");
	ptr2 = _strstr("tarentino est pas ouf en vrai", "banane");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 2 passed\n", achieved++);
	else
		printf("\033[0;31mtest 2 failed\n");

	
	count += 1;
	ptr1 = strstr("tarentino est pas ouf en vrai", "tarentino eSt pas ouf en vrai");
	ptr2 = _strstr("tarentino est pas ouf en vrai", "tarentino eSt pas ouf en vrai");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 3 passed\n", achieved++);
	else
		printf("\033[0;31mtest 3 failed\n");

	
	count += 1;	
	ptr1 = strstr("tarentino est pas ouf en vrai", "");
	ptr2 = _strstr("tarentino est pas ouf en vrai", "");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 4 passed\n", achieved++);
	else
		printf("\033[0;31mtest 4 failed\n");

	count += 1;	
	ptr1 = strstr("tarentino est pas ouf en vrai", "o");
	ptr2 = _strstr("tarentino est pas ouf en vrai", "o");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 4 passed\n", achieved++);
	else
		printf("\033[0;31mtest 4 failed\n");

	count += 1;	
	ptr1 = strstr("tarentino est pas ouf en vrai!", "vrai");
	ptr2 = _strstr("tarentino est pas ouf en vrai!", "vrai");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 4 passed\n", achieved++);
	else
		printf("\033[0;31mtest 4 failed\n");


	count += 1;	
	ptr1 = strstr("tarentino est pas ouf en vrai", "ouf");
	ptr2 = _strstr("tarentino est pas ouf en vrai", "ouf");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 4 passed\n", achieved++);
	else
		printf("\033[0;31mtest 4 failed\n");


	count += 1;
	ptr1 = strstr("", "oui vas y OuiOui");
	ptr2 = _strstr("", "oui vas y OuiOui");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 5 passed\n", achieved++);
	else
		printf("\033[0;31mtest 5 failed\n");

	
	count += 1;
	ptr1 = strstr("oui", "oui vas y OuiOui");
	ptr2 = _strstr("oui", "oui vas y OuiOui");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 6 passed\n", achieved++);
	else
		printf("\033[0;31mtest 6 failed\n");


	count += 1;
	ptr1 = strstr("oui vas y OuiOui", "oui");
	ptr2 = _strstr("oui vas y OuiOui", "oui");
	printf("\033[0;00m\n[%p]\n[%p]\n", ptr1, ptr2);
	if (ptr1 == ptr2)
		printf("\033[0;32mtest 7 passed\n", achieved++);
	else
		printf("\033[0;31mtest 7 failed\n");


	printf("\n\033[0;32m-----Passed %i out of %i-----\n\033[0;00m", achieved, count);
}
