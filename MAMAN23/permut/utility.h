/*	
	permcmp - Permutation comparison.

    This func determines if a word from a file is a permutation of arg.
	Assume arg is already sorted in increasing character order.
	Sort word in increasing character order and check if arg and word are same. 	

	parameters:
				word - pointer to string, to be checked if perm of arg.
				arg - pointer to ordered string of chars.
				len - the length of both arg and word.

	return:
			1 - if word is a permutation of arg.
			0 - if word is NOT a permutation of arg.
*/
int permcmp(char *word, char *arg, size_t len);


/*  Compare function as argument for stdlib qsort(). 
 	Gets 2 void pointers and returns the diff between their 1st char value.
	Returns zero if the two chars are equal, negative int if x is bigger, 
	and positive int if y is bigger.
*/
int compare(const void *x, const void *y);


typedef enum {false, true} bool;

#define MAX 512
