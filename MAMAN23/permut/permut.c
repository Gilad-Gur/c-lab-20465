#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

#define ARGSNUM 3

bool is_file_empty(FILE *file);
bool validate_file_open(FILE *file);
bool validate_argc(int argc);

/*
	Author: Gilad Gur 300622750
	Version: 07.06.2018 (JUNE)

	This program gets a text file path and a string and prints any
	permutations of the string that exists in the text file.

	First, check if the number of arguments is valid for program.
	Check if file given is opepened successfully, and if file is non-empty.
	If any of the above occur, the program prints the appropriate error message
	to the standard error output, and exits normally.
 
	Assuming that the input is valid and non-empty, the program executes 
	the following ALGORITHM:

	1. sort string arg.
	2. get word from file.
	3. if word is shorter: 
			ignore and goto 2. 
	   else - word is longer than, or the same length as arg: 
	   		then for any consecutive sub-word in word, 
				check if it is a permutation of arg (using permcmp function).
		example:
			if
				arg = "abc"
				word = "abacd"
			then
				all sub-words to be checked are:
				1) "aba"
				2) "bac"
				3) "acd"
					in exactly this order.
			
	4. repeat 3 until EOF is reached.

	NOTE: Please read utility.h to understand 
			the concept behind permcmp function.
*/

int main(int argc, char *argv[])
{
	/* declare variables */
	FILE *file;
	char arg[MAX]; 		/* pointer to string arg */
	char word[MAX]; /* buffer for each word read from file */
	int i, diff;
	size_t arglen, wordlen, count; /* count counts num of permutations found */
	
	/* check num of args */
	if (validate_argc(argc))
	{
		return EXIT_FAILURE;
	}

	/* initialize variables */
	file = fopen(argv[1], "r");
	strcpy(arg, argv[2]);

	/* check if file was opened successfully*/
	if (validate_file_open(file))
	{
		return EXIT_FAILURE;
	}

	/* get first word in file */
	fscanf(file, "%s", word);

	/* check if file is non-empty */
	if (is_file_empty(file))
	{
		fclose(file);	
		return EXIT_FAILURE;
	}
	/* get length of string arg */
	arglen = strlen(arg);
	
	/* initialize count */
	count = 0;

	/* sort arg */
	qsort(arg, arglen, sizeof(char), compare);

	/* print any permutation of arg in file in order of appearance */
	do
	{
		/* get length of current word */
		wordlen = strlen(word);
		/* get difference of word and arg lengths */
		diff = wordlen - arglen;
		
		/* if word is shorter than arg then it's not a permutation */
		if (diff < 0)
			continue;

		/*
		 word is longer than, or the same length as arg, 
			then for any consecutive sub-word in word, 
				check if it is a permutation of arg.
			 For more info read first comment in this program file.
		 Also, count any permutations found.
		*/
		for (i=0; i<=diff; i++)
			if(permcmp(word+i, arg, arglen))
			{
				printf("%.*s\n", (int)arglen, word+i);
				count++;
			}

	} while (fscanf(file, "%s", word) != EOF);

	/* 
		if no permutations found at all,
		 then print an appropriate message.	
	*/
	if (count == 0)
		printf("Sorry, No permutations of %s found in %s.\n", argv[2], argv[1]);
	else
		printf("%d permutation instances of %s found in %s.\n", 
												  (int)count, argv[2], argv[1]);

	/* close file pointer */
	fclose(file);

	return EXIT_SUCCESS;
}


/* validate number of arguments to be exactly ARSNUM as defined  */
bool validate_argc(int argc)
{
	if (argc != ARGSNUM)
	{
		if (argc < ARGSNUM)
			fprintf(stderr, "Error: Too few arguments.\n");

		else
			fprintf(stderr, "Error: Too many arguments.\n");

		return true;
	}
	return false;
}

/* validate file was opened successfully */
bool validate_file_open(FILE *file)
{
	if (file == NULL)
	{
		fprintf(stderr, "Error: unable to open file.\n");

		return true;
	}
	return false;
}

/* check if file is empty */
bool is_file_empty(FILE *file)
{
	if (feof(file))
	{
		fprintf(stderr, "Error: file is empty.\n");

		return true;
	}
	return false;
}
