#include <stdio.h>
#include <ctype.h>

#define MAX_LEN 80 

/* 
	This program gets a string, finds all case-sensitive,
	alphabetical order sequences of 3 or more english letters 
	and shortens the string.
	All mentioned sequences will be shortened to a
	sequence of:
	1'st-letter *dash* last-letter
	Example:
	Input: ABabcQRST123zyx
	Output: ABa-cQ-T123zyx
*/

enum status {OUT, TWO, SEQ};

void shortString(char str[]);

int main()
{
	char str[MAX_LEN];
	printf("Please enter a string: \n");
	fgets(str, MAX_LEN + 1, stdin);
	printf("Input string is %s\n", str);
	shortString(str);
	printf("Shortened string is: %s\n", str);
	return 0;
}

void shortString(char str[])
{
	int i = 0;
	int j = i + 1;
	int k;
	enum status state;
	state = OUT;

	while (str[i] != '\0')
	{
		switch(state)
		{
			case OUT:
				/* check if curent char is a letter */
				if ( isalpha(str[i]) ) 
				{
					if ((str[j] - str[i]) == (j - i)) 
					{
						state = TWO;
						++j;
					}
					else
					{
						++i;
						j = i + 1;
					}
				}
				else
				{
					++i;
					j = i + 1;
				}
				break;
			case TWO:
				if ( ((str[j] - str[i]) == (j - i)) && isalpha(str[j]) )
				{
					state = SEQ;
					++j;
				}
				else
				{
					state = OUT;
				}
				break;
			case SEQ:
				if ( (str[j] - str[i]) == (j - i) && isalpha(str[j]) )
				{
					++j;
				}
				else
				{
					str[i+1] = '-';
					str[i+2] = str[j-1];
					k = i + 3;
					while (str[j] != '\0')
					/* copy the rest of the string to its new place */
					{
						str[k] = str[j];
						++k;
						++j;
					}
					str[k] = '\0';
					i += 3;
					j = i + 1;
					state = OUT;
				}
				break;
		}
	}
}
