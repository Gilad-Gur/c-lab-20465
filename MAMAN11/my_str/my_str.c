#include <stdio.h>
#define MAX_SIZE 80

int suffix(char str[], char ch);

/*
	This program takes a char and a string input from the user, and
	prints all the substrings in string that start with the given char
*/

int main()
{
	char ch, c;
	char str[MAX_SIZE];
	int i;

	printf("Please enter a char:\n");
	ch = getchar();
	
	printf("Please enter a string:\n");
	/* Get string input */
	getchar();
	i = 0;
	while ((c = getchar()) != '\n' && c != EOF && i <= MAX_SIZE) 
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	/* Got string input */

	printf("\nYour char is: %c, and your string is: %s\n", ch, str);

	suffix(str, ch);

	printf("\n");

	return 0;
}

/* This function gets a char and a string.
	It prints all substrings that start with ch
	and returns the number of substrings printed */

int suffix(char str[], char ch)
{
	int i, j, count;
	
	count = 0;
	i = 0;
	while (str[i] != '\0') 
	{
		if (str[i] == ch) 
		{
			++count;
			j = i;
			putchar('\n');
			while (str[j] != '\0') {
				putchar(str[j]);
				++j;
			}
		}	
		++i;
	}
	return count;
}

