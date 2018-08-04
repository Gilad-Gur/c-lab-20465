#include <stdlib.h>
#include <stdio.h>
#include "datastructures.h"

#define WORD_SIZE 14
#define BITS_IN_BYTE 8
#define MIN(A,B) ((A<B)?A:B)

/*
this returns a newly malloc'd pointer to 14 char array
	represents 14bit word.
*/
char *create_word(void)
{
	char *ret_p = (char*)malloc( (WORD_SIZE + 1) * sizeof(char));

	return ret_p;
}

/*
this function gets a 14bit array of chars (a word)
	and frees its memory allocation.
*/
void destroy_word(char *word)
{
	free(word);
}

/* 
this function gets a ptr to array of 14 bit chars, each char is '0' or '1'
	returns a ptr to array of 14 bit chars of "weird" base, 
	i.e it returns a similar array to the argument given, 
	replacing each '0' with '.' and replacing each '1' with '/' 
*/
char *from_binary_to_weird(char *binary_word_p)
{
	char *ret_p =  create_word();/* allocating memory for weird word,
															the array pointer to be returned*/
	char *runner_p; /* a temp runner to assign values in ret_p */

		
	runner_p = ret_p; /* initialize runner to point to first char of result */

	/* assign each cell with appropriate char */
	while(*binary_word_p != '\0')
	{
		if (*binary_word_p == '0')
			*runner_p = '.';
		else
			*runner_p = '/';

		++runner_p;
		++binary_word_p;
	}
	/* assign end of string flag*/
	*runner_p = '\0';

	return ret_p;
	
}

/*
this function gets a number or a letter and returns its 14bit representation.
	14bit represntation is an array of 14 chars, each one is 1 or 0.
	assume the arg is in the valid range of -8192 up to 8191.
	gets also parameter size_of_var that represents sizeof(var) in bytes.
*/
char *var_to_word(void *var, size_t size_of_var)
{
	char *ret_p = create_word(); /* allocate memory for result */

	int size_of_var_in_bits = size_of_var * BITS_IN_BYTE;

	int min_size = MIN(size_of_var_in_bits, WORD_SIZE);
	
	char *runner_p = ret_p; /* define temp ptr to assign values */

	int i, mask;

	runner_p += WORD_SIZE;
	
	*runner_p = '\0';

	for (i=0; i<min_size; i++)
	{
		runner_p--;

		mask = (1 << i);

		if  ((*(int *)var) & mask)
		{
			*runner_p  = '1';
		}
		else
			*runner_p = '0';
	}

	if (WORD_SIZE > min_size)
	{
		for (i=min_size; i<WORD_SIZE; i++)
		{
			runner_p--;

			*runner_p = '0';
		}
	}

	return ret_p;
}

/*
This function gets a pointer to a variable (number or string)
and it also gets a flag if it is a number or a string,
and returns the number of memory words it needs to represent it
in machine form
*/
int num_of_memory_words(void *var, boolean isWord)
{
	int counter = 0;
	char *cptr = (char*)var;

	if (isWord)
	{
		while(*cptr != '\0')
		{
			counter++;
			cptr++;
		}
	}
	else
		counter = 1;
	
	return counter;
}


/************/
/*debug only*/
/************/
int main()
{
	int a;

	char *binary_word;
	char *result1;
	char *result2;
	char *result3;
	char *result4;
	char *result5;

	char *ab = "ab";
	char *abc = "abc";
	char *abcd = "abcd";
	char *abcde = "abcde";
	int t1 = 123;
	int t2 = 98;

	binary_word = "10101010101010";

	result1 = from_binary_to_weird(binary_word);

	a = 650;
	result2 = var_to_word(&a, sizeof(a));
	a = -1;
	result3 = var_to_word(&a, sizeof(a));
	a = 99999;
	result4 = var_to_word(&a, sizeof(a));
	a = 'a';
	result5 = var_to_word(&a, sizeof(a));

	printf("%s\n", binary_word); 
	printf("%s\n", result1); 

	printf("var_to_word(650)   -> %s\n", result2);
	printf("var_to_word(-1)    -> %s\n", result3);
	printf("var_to_word(99999) -> %s\n", result4);
	printf("var_to_word('a')   -> %s\n", result5);


	printf("num_of_mem_words   -> %d\n", num_of_memory_words(ab,true));
	printf("num_of_mem_words   -> %d\n", num_of_memory_words(abc,true));
	printf("num_of_mem_words   -> %d\n", num_of_memory_words(abcd,true));
	printf("num_of_mem_words   -> %d\n", num_of_memory_words(abcde,true));
	printf("num_of_mem_words   -> %d\n", num_of_memory_words(&t1,false));
	printf("num_of_mem_words   -> %d\n", num_of_memory_words(&t2,false));
	
	
	destroy_word(result1);
	destroy_word(result2);
	destroy_word(result3);
	destroy_word(result4);
	destroy_word(result5);

	return 0;
}
