typedef struct set set;

/* 
	set_bit_on function gets a struct set and an index and sets the bit at index on.
	if a bit at index is already on, then it will be left on.

	parameters:
				s - pointer to first byte of passed set.
				index - int to represents the bit to be set on.
 */
void set_bit_on(set *s, int index);

/*
	create_set function allocates the needed memory space to create a new set
	and returns a pointer to the first byte of the new set.

	return:
			ret - pointer to first byte of the newly created set. 
 
*/
set* create_set(void);

/*
	destroy_set function frees up the space allocated to the argument set 
	'to_destroy' while it was created.

	parameters:
				to_destroy - a pointer to the set that will be destroyed. 
*/
void destroy_set(set *to_destroy);

/*
	read_set function allows the user to insert integer values (range:0-127 inc.)
	into a selected valid set.
	Each call to this function will delete the previous data in the used set.

	parameters:
				s - pointer to destination set.
				num - pointer to int args array (contains number args by user).
				n - length of num array.
*/
void read_set(set *s, int *num, int n);

/*
	print_set function allows the user to print the data contained by a set.
	It will print in ascending order the values of that set, 
	up to 16 values per line.

	parameters:
				s - pointer to set to be printed
*/
void print_set(set *s);

/*
	union_set function provides the user with the option to perform the mathematical
	operation of sets union on 2 sets. 
	A third set will be inserted with the result.

	parameters:
				set1 - pointer to set argument 1.
				set2 - pointer to set argument 2.
				result - pointer to set to be inserted with union result.
	
	NOTE: the same set can be passed as any argument in the argument list.
*/
void union_set(set *set1, set *set2, set *result);


/*
	intersect_set function provides the user with the option to perform the 
	mathematical operation of sets intersection on 2 sets. 
	A third set will be inserted with the result.

	parameters:
				set1 - pointer to set argument 1.
				set2 - pointer to set argument 2.
				result - pointer to set to be inserted with intersection result.
	
	NOTE: the same set can be passed as any argument in the argument list.
*/
void intersect_set(set *set1, set *set2, set *result);


/*
	sub_set function provides the user with the option to perform the mathematical
	operation of sets subtraction on 2 sets. 
	A third set will be inserted with the result.

	parameters:
				set1 - pointer to set argument 1.
				set2 - pointer to set argument 2.
				result - pointer to set to be inserted with subtraction result.
	
	NOTE: the same set can be passed as any argument in the argument list.
*/
void sub_set(set *set1, set *set2, set *result);

/*
	stop function provides the user with a way to terminate the set operations
	program.

	If the stop function is invoked, then the program will exit successfully.
*/
void stop(void);
