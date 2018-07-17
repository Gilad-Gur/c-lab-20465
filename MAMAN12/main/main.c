#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "my_bcmp.h"

#define MAX_LENGTH 512

/* declaring prototypes */
int my_bcmp(const void *b1, const void *b2, size_t len);
int validateInt(char *input);

/*
	Main function of my_bcmp.
	A) Gets and validates user input.
		If an argument passed is not valid
			then the program exits with an appropriate messege.
	B) Invokes my_bcmp() with user input.
	C) Prints result of my_bcmp() and memcmp().
	D) Exits normally.

	Method used for performing A:
	1) Getting an input argument as a string.
	2) Check if the string contains valid data only 
		that represents the destination variable to be assigned.
		for example: getting an index arg as a string and 
		verifying all chars are digits, hence the input data is an integer.
	3) Convert the string input to a desired variable/constant type.
		Following the ex. from (2), converting the given index 
		from string	type to integer type. 
*/

int main(void)
{
	/* declare variables */
	/* string variables for user-input */
	char input_len[MAX_LENGTH];
	char input_index1[MAX_LENGTH];
	char input_index2[MAX_LENGTH];
	char str[MAX_LENGTH];

	/* variables that will be used to pass arguments to my_bcmp() */
	size_t len;
	int index1, index2;
	char *b1, *b2;

	/* variables for testing purposes */
	int result; 	/* = my_bcmp(b1, b2, len) */
	int ref_result; /* = memcmp(b1, b2, len) */
	

	/* get & validate len argument for my_bcmp() */
	printf("Please enter len (number of bytes to be compared):\n");
	fgets(input_len, MAX_LENGTH, stdin);

	if (validateInt(input_len) == 0)
	{
		len = atoi(input_len); /* convert input string to int */
	}
	else
	{
		printf("INVALID LEN INPUT: NEED INTEGER\n");
		exit(EXIT_FAILURE);
	}
	
	if (len > MAX_LENGTH)
	{
		printf("INVALID LENGTH INPUT: NEED NUMBER <= 512 \n");
		exit(EXIT_FAILURE);
	}

	/* get & validate index1 argument for my_bcmp() */
	printf("Please enter index1:\n");
	fgets(input_index1, MAX_LENGTH, stdin);

	if (validateInt(input_index1) == 0)
	{
		index1 = atoi(input_index1); /* convert input string to int */
	}
	else
	{
		printf("INVALID INDEX1 INPUT: NEED INTEGER\n");
		exit(EXIT_FAILURE);
	}
	/* check that len & index1 is logical in relation to max size of str */
	if (MAX_LENGTH < (len + index1)) 
	{
		printf("INVALID INDEX1 INPUT: NEED NUMBER <= %lu\n", 
				MAX_LENGTH - ((unsigned long)len));
		exit(EXIT_FAILURE);
	}
	/* get & validate index2 argument for my_bcmp() */
	printf("Please enter index2:\n");
	fgets(input_index2, MAX_LENGTH, stdin);
	if (validateInt(input_index2) == 0)
	{
		index2 = atoi(input_index2); /* convert input string to int */
	}
	else
	{
		printf("INVALID INDEX2 INPUT: NEED INTEGER\n");
		exit(EXIT_FAILURE);
	}

	/* check that len & index2 is logical in relation to max size of str */
	if (MAX_LENGTH < (len + index1)) 
	{
		printf("INVALID INDEX1 INPUT: NEED NUMBER <= %lu\n", 
				MAX_LENGTH - ((unsigned long)len));
		exit(EXIT_FAILURE);
	}
	if (MAX_LENGTH < (len + index2))
	{
		printf("INVALID INDEX2 INPUT: NEED NUMBER <= %lu\n", 
				MAX_LENGTH - ((unsigned long)len));
		exit(EXIT_FAILURE);
	}

	/* get string from user */
	printf("Please enter a string\n");
	fgets(str, MAX_LENGTH, stdin);

	/* all input is valid and ready to execute */
	printf("Input:\nlen = %lu\nindex1 = %d\nindex2 = %d\nstring =\n%s\n",
			len, index1, index2, str); 
	b1 = str + index1;
	b2 = str + index2;
	result = my_bcmp(b1, b2, len);
	ref_result = memcmp(b1, b2, len);
	printf("my_bcmp(b1, b2, len) -> %d\nmemcmp(b1, b2, len) -> %d\n", 
			result, ref_result);

	/* end program */
	return(0);
}

/*
	This function gets a string of chars 
	& determines if all the chars are digits.
	Returns 0 if yes, otherwise returns 1.
*/

int validateInt(char *input)
{

	while (*input != '\n' && *input != '\0')
	{
		if (*input < '0' || *input > '9')
		{
			return 1;
		}
		++input;
	}

	return 0;
}

