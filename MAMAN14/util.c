#include <stdio.h>
#include <ctype.h>
#include "util.h"

#define MAX 80

/* return 0 false or 1 true */
int iswhiteline(char *linep)
{
	while (*linep != '\0')
	{
		if (!isspace(*linep))
			return 0;
		++linep;
	}
	return 1;
}

void copycleanfile(FILE *src, FILE *dest)
{
		char *cp;
		char line[MAX];

		while (fgets(line,MAX,src))
		{
			/* ignore white space line */
			if (iswhiteline(line))
			{
				continue;
			}

			cp = line;

			/* ignore white spaces */
			while (isspace(*cp))
			{
				++cp;
			}
			/* ignore comment line */
			if (*cp == ';')
			{
				continue;
			}

			/* copy content to dest file */
			fputs(cp, dest);
		}
}


/* 
	this function gets a ptr to file with binary digits
	and converts 0's to . and 1's to / 

	returns a ptr to the new file.
*/
void binarytoweird(FILE *src, FILE *dest)
{
	char c;

	while ( (c=fgetc(src)) != EOF)
	{
		if (c=='0')
			fputc('.',dest);
		if (c=='1')
			fputc('/',dest);
		if (c=='\n')
			fputc('\n',dest);
	}
}
