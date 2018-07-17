#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
 
int compare(const void *x, const void *y)
{
    return (*(char *)x - *(char *)y);
}


int permcmp(char *word, char *arg, size_t len)
{
	char sorted_word[MAX];

	strcpy(sorted_word, word);
	qsort(sorted_word, len, sizeof(char), compare);
	
	if (memcmp(sorted_word, arg, len) == 0)
	{
		return (1);
	}

	/* word is not a permutation of arg */
	return (0);
}

 
