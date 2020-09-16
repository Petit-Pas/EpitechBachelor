
#include <criterion/criterion.h>
#include <stdio.h>

char *rindex(const char *, int);
char *_memcpy(void *, const void *, int);
void *_memmove(void *, const void *, int);
int _strcmp(char *, char *);
void *_memset(void *, int, int);

Test(strcmp, test_OK)
{
	cr_assert_eq(_strcmp("ABCD", ""), 'A');
	cr_assert_eq(_strcmp("ABCD", "ABC"), 'D');
	cr_assert_eq(_strcmp("ABCD", "ABCC"), 1);
	cr_assert_eq(_strcmp("ABCC", "ABCD"), -1);
	cr_assert_eq(_strcmp("ABCE", "ABCC"), 2);
	cr_assert_eq(_strcmp("ABCC", "ABCE"), -2);
	cr_assert_eq(_strcmp("ABCD", "ABCD"), 0);
	cr_assert_eq(_strcmp("", ""), 0);
	printf("\033[0;32m[strcmp tests]: passed\n");
}

Test(memcpy, test_OK)
{
	char *str = strdup("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	char buffer[26];
	char buff[26];

	_memcpy(buffer, &str[5], 15);
	memcpy(buff, &str[5], 15);
	cr_assert_eq(strcmp(buffer, buff), 0);	
	printf("[\033[0;32mmemcpy tests]: passed\n");
}

Test(_memmove, test_OK)
{
	char *buffer = strdup("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	char *buffer2 = strdup("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	void *ptr = _memmove(buffer, &buffer[5], 15);
	void *ptr1 = memmove(buffer2, &buffer2[5], 15);
	cr_assert_eq(strcmp(buffer, buffer2), 0);
	printf("[\033[0;32mmemmove tests]: passed\n");
}

Test(_memset, test_OK)
{
	char buff[11];

	memset(buff, 0, 11);
	_memset(buff, 'A', 10);
	cr_assert_eq(strcmp(buff, "AAAAAAAAAA"), 0);
	printf("[\033[0;32mmemset tests]: passed\n");
}

char *_rindex(const char *s, int c);

Test(rindex, test_ok)
{
	char *buff = strdup("ABCDEFGABCDEFG");
	char *ptr1 = _rindex(buff, 'G');
	char *ptr2 = rindex(buff, 'G');

	cr_assert_eq(ptr1, ptr2);
	ptr1 = _rindex(buff, 'Z');
	ptr2 = rindex(buff, 'Z');
	cr_assert_eq(ptr1, ptr2);	
	printf("[\033[0;32mrindex tests]: passed\n");
}

int _strcasecmp(const char *s1, const char *s2);

Test(strcasecmp, test_OK)
{
	char *buff1 = strdup("bonjour");
	char *buff2 = strdup("bonjour");

	cr_assert_eq(strcasecmp(buff1, buff2), _strcasecmp(buff1, buff2));
	buff1 = strdup("BONJOUR");
	buff2 = strdup("bonjour");
	cr_assert_eq(strcasecmp(buff1, buff2), _strcasecmp(buff1, buff2));
	buff1 = strdup("BONJOURa");
	buff2 = strdup("bonjourb");
	cr_assert_eq(strcasecmp(buff1, buff2), _strcasecmp(buff1, buff2));
	printf("[\033[0;32mstrcasecmp tests]: passed\n");
}

char *_strchr(const char *, int c);

Test(strchr, test_OK)
{
	char *buff = strdup("ABCDEFGABCDEFG");
	char *ptr1 = _rindex(buff, 'G');
	char *ptr2 = rindex(buff, 'G');

	cr_assert_eq(ptr1, ptr2);
	ptr1 = strchr(buff, 'Z');
	ptr2 = _strchr(buff, 'Z');
	cr_assert_eq(ptr1, ptr2);
	ptr1 = strchr(buff, 0);
	ptr2 = _strchr(buff, 0);
	cr_assert_eq(ptr1, ptr2);
	buff = strdup("");
	ptr1 = strchr(buff, 0);
	ptr2 = _strchr(buff, 0);
	cr_assert_eq(ptr1, ptr2);
	printf("[\033[0;32mstrchr tests]: passed\n");
}

int _strcspn(const char *, const char *);

Test(_strcspn, test_OK)
{
	cr_assert_eq(_strcspn("bonjour je suis un lapin", "as"), strcspn("bonjour je suis un lapin", "as"));
	cr_assert_eq(_strcspn("bonjour je suis un lapin", ""), strcspn("bonjour je suis un lapin", ""));
	printf("[\033[0;32mstrcspn tests]: passed\n");
}

int _strlen(const char *);

Test(_strlen, test_OK)
{
	cr_assert_eq(_strlen("bonjour je suis"), strlen("bonjour je suis"));
	cr_assert_eq(_strlen(""), strlen(""));

	printf("[\033[0;32mstrlen tests]: passed\n");
}

int _strncmp(char *, char *, int);

Test(_strncmp, test_OK)
{
	cr_assert_eq(_strncmp("ABCD", "", 10), 'A');
	cr_assert_eq(_strncmp("ABCD", "ABC", 10), 'D');
	cr_assert_eq(_strncmp("ABCD", "ABCC", 10), 1);
	cr_assert_eq(_strncmp("ABCC", "ABCD", 10), -1);
	cr_assert_eq(_strncmp("ABCE", "ABCC", 10), 2);
	cr_assert_eq(_strncmp("ABCC", "ABCE", 10), -2);
	cr_assert_eq(_strncmp("ABCD", "ABCD", 10), 0);
	cr_assert_eq(_strncmp("", "", 10), 0);
	cr_assert_eq(_strncmp("ABCD", "", 10), 'A');
	cr_assert_eq(_strncmp("ABCD", "ABC", 3), 0);
	cr_assert_eq(_strncmp("ABCD", "ABCC", 3), 0);
	cr_assert_eq(_strncmp(NULL, NULL, 0), strncmp(NULL, NULL, 0));
	printf("[\033[0;32mstrncmp tests]: passed\n");
}

char *_strstr(const char *, const char *);

Test(_strstr, test_OK)
{
//	char *buffer = strdup(" il etais une fois une marchand de foie qui mangeait du foie dans la ville de Foie, elle s'est dit ma foi si je mange du foie, je sais plus la suite");
	const char buffer[] = "tarentino n'est pas ouf en vrai";
	const char buffer2[] = "tarentino n'est pas ouf en vrai !";
        char *ptr1 = strstr(buffer, buffer2);
	//char *ptr2 = _strstr(buffer, "Foie");
	char *ptr2 = _strstr(buffer, buffer2);
	printf("%p and %p\n%s and %s\n", ptr1, ptr2, ptr1, ptr2);
	cr_assert_eq(ptr1, ptr2);
	ptr1 = strstr(buffer, "biloute");
	ptr2 = _strstr(buffer, "biloute");
	cr_assert_eq(ptr1, ptr2);

	char *str = strdup("");
	char *str1 = strdup("");
	cr_assert_eq(strstr(str, str1), _strstr(str, str1));
	printf("[\033[0;32mstrstr tests]: passed\n");
}

char *_strpbrk(char *, char *);

Test(_strpbrk, test_OK)
{
	char *str = strdup("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	void *ptr = _strpbrk(str, "12345678M");
	void *ptr2 = strpbrk(str, "12345678M");;
	cr_assert_eq(ptr, ptr2);
	ptr = _strpbrk(str, "123456789");
	ptr2 = strpbrk(str, "123456789");;
	cr_assert_eq(ptr, ptr2);
	printf("[\033[0;32mstrpbrk tests]: passed\n");
}

int getnbr(char *str);

Test(getnbr, test_OK)
{
	cr_assert_eq(getnbr("12"), 12);
	cr_assert_eq(getnbr("-12"), -12);
	cr_assert_eq(getnbr("--12"), 12);
	cr_assert_eq(getnbr("-+12"), -12);
	cr_assert_eq(getnbr("-A12"), 0);
	cr_assert_eq(getnbr("A12"), 0);
	cr_assert_eq(getnbr("-1A2"), -1);
	cr_assert_eq(getnbr("-12A"), -12);
	cr_assert_eq(getnbr("-1-2"), -1);
	printf("[\033[0;32mgetnbr tests]: passed\n");
}

int counter();
void increase();
void decrease();
void display();
void add(int);
void sub(int);

Test(thermometer, test_OK)
{
	printf("\x1B[37m");
	display();
	cr_assert_eq(counter(), 0);
	increase();
	display();
	cr_assert_eq(counter(), 1);
	decrease();
	display();
	cr_assert_eq(counter(), 0);
	add(10);
	display();
	cr_assert_eq(counter(), 10);
	sub(10);
	display();
	cr_assert_eq(counter(), 0);
	printf("\033[0;32m[thermometer tests]: passed\n");
}

char *_strcpy(char *str, char *);

Test(_strcpy, test_OK)
{
	char *str = strdup("bonjour");
	char buff[100];

	_strcpy(buff, str);
	cr_assert_eq(strcmp(buff, str), 0);
	printf("\033[0;32m[strcpy tests]: passed\n");
}

char **str_to_wordtab(char *);

Test(str_to_wordtab, test_OK)
{
	char *str = strdup("  bonjour je  suis      une str   ");
	char **tab = str_to_wordtab(str);

	cr_assert_eq(strcmp(tab[0], "bonjour"), 0);
	cr_assert_eq(strcmp(tab[1], "je"), 0);
	cr_assert_eq(strcmp(tab[2], "suis"), 0);
	cr_assert_eq(strcmp(tab[3], "une"), 0);
	cr_assert_eq(strcmp(tab[4], "str"), 0);
	cr_assert_eq(tab[5], NULL);
	printf("\033[0;32m[str_to_wordtab tests]: passed\n");
}
