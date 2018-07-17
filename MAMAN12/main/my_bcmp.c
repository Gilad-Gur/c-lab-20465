#include <stddef.h>

int my_bcmp(const void *b1, const void *b2, size_t len)
{
	const unsigned char *b1Char = b1;
	const unsigned char *b2Char = b2;

	while (len > 0)
	{
		if (*b1Char != *b2Char)
		{
			return (*b1Char - *b2Char);
		}

		++b1Char;
		++b2Char;
		--len;
	}

	return (0);
}

