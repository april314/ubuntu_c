#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "password.h"

char * password(int pswd_len)
{
	int count = 0;
	//int digits = 0, lower = 0, upper = 0, other = 0;
	char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxwz1234567890`~!@#$%^&*()_+";
	char *  passwd = malloc(pswd_len);  //in a heap, cause we need to return it (and local variables die)

	srandom(time(NULL));

	while (count < pswd_len) {
		passwd[count] = chars[random()%75];
		++count;
	}

	return passwd;
}
