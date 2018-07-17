#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

#define NUM_OF_BYTES 16
#define SIZE_OF_BYTE 8
#define NUM_OF_BITS 128
#define PRINT_NEWLINE 16

void set_bit_on(set *s, int index);
int bit_is_on(set *s, int index);

struct set
{
	char bit_array[NUM_OF_BYTES];
};

void read_set(set *s, int *num, int n)
{

	int i;
	for (i=0; i<n && *num!=-1; i++)
	{
		set_bit_on(s, *num);
		++num;
	}
}

void print_set(set *s)
{
	int i, empty, counter;

	empty = 1;
	for (i=0; i<NUM_OF_BITS; i++)
		if (bit_is_on(s, i))
		{
			empty = 0;
			++counter;

			if(counter%PRINT_NEWLINE == 0)
				printf("\n\t");

			printf(" %d ", i);
		}
	if(empty)
		printf("This set is empty.");
}

void union_set(set *set1, set *set2, set *result)
{
	set *temp;
	int i;

	temp = create_set();
	for (i=0; i<NUM_OF_BITS; i++)
		if (bit_is_on(set1, i) || bit_is_on(set2, i))
			set_bit_on(temp, i);

	memcpy(result, temp, NUM_OF_BYTES);
	destroy_set(temp);
}

void intersect_set(set *set1, set *set2, set *result)
{
	set *temp;
	int i;

	temp = create_set();
	for (i=0; i<NUM_OF_BITS; i++)
		if (bit_is_on(set1, i) && bit_is_on(set2, i))
			set_bit_on(temp, i);

	memcpy(result, temp, NUM_OF_BYTES);
	destroy_set(temp);
}
void sub_set(set *set1, set *set2, set *result)
{
	set *temp;
	int i;

	temp = create_set();
	for (i=0; i<NUM_OF_BITS; i++)
		if (bit_is_on(set1, i) && !bit_is_on(set2, i))
			set_bit_on(temp, i);

	memcpy(result, temp, NUM_OF_BYTES);
	destroy_set(temp);
}

void stop(void)
{
	exit(EXIT_SUCCESS);
}

set* create_set(void)
{
	set *ret = (set*)calloc(NUM_OF_BYTES, SIZE_OF_BYTE);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

void destroy_set(set* to_destroy)
{
	free(to_destroy);
}

void set_bit_on(set *s, int index)
{
	s->bit_array[index/SIZE_OF_BYTE] |= 1 << index%SIZE_OF_BYTE;
}

int bit_is_on(set *s, int index)
{
	return !!(s->bit_array[index/SIZE_OF_BYTE] & (1<<index%SIZE_OF_BYTE));
}
