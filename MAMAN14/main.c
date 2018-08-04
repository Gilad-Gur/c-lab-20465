#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		fprintf(stderr, "Err: too few arguments\n");
		exit(EXIT_FAILURE);
	}
	FILE *psrc = fopen(argv[1], "r");
	FILE *pdest = tmpfile();
	FILE *psrc2 = fopen(argv[2], "r");
	FILE *pdest2 = fopen("result.ob", "w");
	char c;

	copycleanfile(psrc, pdest);

	fseek(pdest, 0, SEEK_SET);

	while((c = fgetc(pdest)) != EOF)
	{
		putchar(c);
	}

	binarytoweird(psrc2,pdest2);

	fclose(psrc);
	fclose(pdest);
	fclose(psrc2);
	fclose(pdest2);

	return (0);
}
