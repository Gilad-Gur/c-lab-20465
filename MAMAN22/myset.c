#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "set.h"

#define FOREVER for(;;)
#define LONGEST_CMD 14
#define SET_ARGS_NUM 3
#define NUM_OF_CMD 6
#define NUM_OF_SETS 6
#define MAX_LEN 512
#define NUM_OF_BYTES 16
#define SET_NAME_LEN 4
#define BASE 10
#define MAX_ARR_SIZE 128
#define STOP_STR_LEN 4

enum status {CMD, SET1, COMMA_AFTER_SET1, SET2, COMMA_AFTER_SET2, RESULT, NUMBER, COMMA_READ, MINUS1, STOP};

/* array of all 6 valid set names  */
static char *sets[]={"SETA","SETB","SETC","SETD","SETE","SETF"};

/* array of all 6 valid command names */
static char *commands[]={"read_set","print_set", "union_set", 
						"intersect_set", "sub_set","stop"};

/* prototype declerations */
int vldcmdln(char *cmdln);
void errmsg(int err);
int vldcmdname(char *cmdln);
int vldsetname(char *cmdln);
int vldnum(char *cmdln);
void execmd(char *cmdln);

int main (void)
{
	int i, command;
	char command_line[MAX_LEN];
	char *cmdln,*set1name;
	int num_array[MAX_ARR_SIZE];
	set* set_array[NUM_OF_SETS];
	set *set1,*set2,*result;

	for (i=0; i<NUM_OF_CMD; i++)
	{
		if((set_array[i] = create_set()) == NULL)
		{
			printf("ERROR: Unable to allocate memory\n");
			return (1);
		}
	}

	/* saying hello to user*/
	printf("Well hello there, and welcome to SET OPERATIONS.\n");
	printf("Let's play around with sets and a few operations on them.\n");
	printf("1. Valid set names only: SETA, SETB, SETC, SETD, SETE, SETF.\n");
	printf("2. Valid opertaions only: read_set, print_set, union_set, ");
	printf("intersect_set, sub_set.\n");
	printf("3. Valid range of numbers: 0-127 inc.\n");
	printf("4. To perform read_set, input as follows:\n");
	printf("read_set <setname>,<number>,...,<number>,-1 <ENTER>\n");
	printf("Example: read_set SETA, 12, 13 ,14 ,-1\n");
	printf("5. To perform print_set, input as follows:\n");
	printf("print_set <setname><ENTER>\n");
	printf("Example: print_set SETA\n");
	printf("6. To perform union/intersect/sub_set, input as follows:\n");
	printf("<operation> <setname1>,<setname2>,<setname3><ENTER>\n");
	printf("Example: intersect_set SETB, SETF, SETD\n");
	printf("NOTE: the same set can be used twice or 3 times ");
	printf("in uni/inter/sub operations.\n");
	printf("7. To quit: stop<ENTER>\n");



		printf("\n\n~prompt: ");
		while(fgets(command_line, MAX_LEN, stdin) != NULL)
		{
			cmdln = command_line;
			printf("\ninput:  %soutput: ", cmdln);
			while (isspace(*cmdln))
				++cmdln;
			if (vldcmdln(cmdln))
			{
				command = vldcmdname(cmdln);
				cmdln += strlen(commands[command]);
				while (isspace(*cmdln))
					++cmdln;
				set1name = sets[vldsetname(cmdln)];
				set1 = set_array[vldsetname(cmdln)];
				cmdln += SET_NAME_LEN;

				switch (command)
				{
					/* read_set */
					case 0:
						i=0;
						while (*cmdln != '\0')
						{
							while (isspace(*cmdln) || *cmdln==',')
								++cmdln;
							num_array[i] = strtol(cmdln, &cmdln, BASE);
							i++;
						}
						memset(set1, 0, NUM_OF_BYTES);
						read_set(set1, num_array, i);
						printf("Done!\n");
						break;

					/* print_set */
					case 1:
						printf("%s: ",set1name);
						print_set(set1);
						printf("\n");
						break;

					/* union_set, interset_set, sub_set */
					case 2: case 3: case 4:
						while(isspace(*cmdln) || *cmdln==',')
							++cmdln;
						set2 = set_array[vldsetname(cmdln)];
						cmdln += SET_NAME_LEN;
						while(isspace(*cmdln) || *cmdln==',')
							++cmdln;
						result = set_array[vldsetname(cmdln)];

						if (command==2)
							union_set(set1, set2, result);
						else if(command==3)
							intersect_set(set1, set2, result);
						else /* command==4 */
							sub_set(set1, set2, result);
						printf("Done!\n");
						break;

					/* stop */
					case 5:
						for(i=0; i<NUM_OF_SETS; i++)
							destroy_set(set_array[i]);
						while (isspace(*cmdln))
							++cmdln;
						printf("Bye bye\n");
						stop();
						break;
				} /* end switch */
			} /* end if vldcmnline */

			printf("\n\n~prompt: ");

		} /* end while(fgets) */	

		if (strcmp(command_line,"stop") != 0)
		{
			printf("Error: no 'stop' command at EOF redirection.\n");
			
			for(i=0; i<NUM_OF_SETS; i++)
				destroy_set(set_array[i]);

			exit(EXIT_FAILURE);
		}

		return (0);
} /* end main */

/*
	vldcmdln - validate command line
	returns 1 if valid
	otherwise, returns 0
*/
int vldcmdln(char *cmdln)
{
	enum status state;
	int command_number;
	int num;

	state = CMD;
	command_number = 0;
	FOREVER
	{
		/* ignore white spaces */
		if (isspace(*cmdln))
		{
			++cmdln;
			continue;
		}
		
		/* state machine to validate command line input */
		switch(state)
		{
			case CMD:
				command_number = vldcmdname(cmdln);
				
				/* if invalid command name */
				if (command_number >= NUM_OF_CMD)
				{
					errmsg(1);
					return(0);
				}
				/* if command is stop*/
				else if (command_number == 5)
				{
					cmdln += strlen(commands[command_number]);
					state = STOP;
				}

				else /* valid command name */
				{
					cmdln += strlen(commands[command_number]);
					state = SET1;
				}
				continue;	

			case SET1:
				/* if cmdname is valid but only whitespace follow */
				if (*cmdln == '\0')
				{
					errmsg(5);
					return (0);
				}
				/* if comma is between command_name and SET1 */
				if (*cmdln == ',')
				{
					errmsg(9);
					return(0);
				}
				else
				{
					/* if set name is valid */
					if (vldsetname(cmdln) != -1)
					{
						cmdln += SET_NAME_LEN;

						/* if cmd is print_set */
						if (command_number == 1)
						{
							/* if remainder of cmdln is valid 
								(only white spaces) */
							while (*cmdln != '\0')
							{
								if (isspace(*cmdln))
								{
									++cmdln;
									continue;
								}
								else
								{
									errmsg(6);
									return (0);
								}
							}
							return (1);
						}
						/* if cmndname is read_set */
						else if(command_number == 0)
						{
							state = COMMA_READ;
						}

						else /* other valid command */
						{
							state = COMMA_AFTER_SET1;
						}
					}

					else /* invalid set name */
					{
						errmsg(0);
						return (0);
					}
				}

				continue;
			

			case COMMA_AFTER_SET1:

				if (*cmdln != ',')
				{
					errmsg(8);
					return (0);
				}

				else
				{
					/* if cmd is read_set */
					if (command_number == 0)
					{
						state = NUMBER;
					}
					/* otherwise inter/uni/sub cmd */
					else
					{
						state = SET2;
					}

					++cmdln;
				}
				continue;
		

			case SET2:

				/* if double comma */
				if (*cmdln == ',')
				{
					errmsg(7);
					return (0);
				}
				/* if missing set parameter */
				if (*cmdln == '\0')
				{
					errmsg(5);
					return (0);
				}
				/* if invalid set name */
				if (vldsetname(cmdln) == -1)
				{
					errmsg(0);
					return (0);
				}

				cmdln += SET_NAME_LEN;
				state = COMMA_AFTER_SET2;
				continue;


			case COMMA_AFTER_SET2:

				/* if there's nothing there */
				if (*cmdln != ',')
				{
					errmsg(8);
					return (0);
				}

				state = RESULT;
				++cmdln;
				continue;


			case RESULT:
				
				/* if there's nothing there */
				if(*cmdln == '\0')
				{
					errmsg(5);
					return (0);
				}

				/* if double comma */
				if (*cmdln== ',')
				{
					errmsg(7);
					return (0);
				}
				/* if invalid set name */
				if (vldsetname(cmdln) == -1)
				{
					errmsg(0);
					return (0);
				}

				cmdln += SET_NAME_LEN;
				while (*cmdln != '\0')
				{
					if (isspace(*cmdln))
					{
						++cmdln;
						continue;
					}
					else
					{
						errmsg(6);
						return (0);
					}
				}
				return (1);

				break;


			case NUMBER:
				
				/* if ended after comma */
				if(*cmdln == '\0')
				{
					errmsg(3);
					return (0);
				}

				/* if double comma */
				if (*cmdln == ',')
				{
					errmsg(7);
					return (0);
				}

				num = vldnum(cmdln);
				/* if invalid num arg */
				if (num == 0)
				{
					return (0);
				}

				/* if num is valid and in range */
				if (num >= 1)
				{
					cmdln += num;
					state = COMMA_READ;
				}
				
				else if (num == -1)
				{
					cmdln += 2;
					state = MINUS1;
				}

				continue;


			case COMMA_READ:
	
				/* if list of nums not ended correctly */
				if(*cmdln == '\0')
				{
					errmsg(3);
					return (0);
				}			

				/* if missing comma */
				if (*cmdln != ',')
				{
					/* if .digit */
					if (*cmdln == '.')
					{
						++cmdln;
						if (isdigit(*cmdln))
						{
							errmsg(4);
						}
					}
					else
					{
						errmsg(8);
					}
					return (0);
				}

				++cmdln;
				state = NUMBER;
				continue;


			case MINUS1:
				
				if (*cmdln != '\0')
				{
					errmsg(6);
					return (0);
				}
				else
				{
					return (1);
				}
				break;

			
			case STOP:
				
				if (*cmdln != '\0')
				{
					errmsg(6);
					return (0);
				}

				return (1);

				break;


			default:
				printf("default switch(?)\n");
				return (0);
				break;
		} /* end switch  */
		
		return (1);
	
	} /* end while commadline!=NULL */
	return 0;
}

/* vldcmdname - validate command name 
	this function gets a string contains the command line
	(pointer to the first char in commandline that is not white space)
	and returns the number of the command in the command array, only
	if the first token in command line is a valid command name. 
	Otherwise returns 6.

	parameter *cmdln - the command line

	return i - an int to represent the number of the 
				command name in the command array.
*/
int vldcmdname(char *cmdln)
{
	int i;
	for (i=0; i<NUM_OF_CMD; i++)
		if (0 == memcmp (cmdln, commands[i], strlen(commands[i])))
			return (i);
	return (i);
}

/*
	vldsetname - validate set name

	This function determiness if the first token of the given string
	is a valid set name, out of the 6 valid set names defined in
	the sets array. 
	It gets a command line string and returns 0-6 to represent the set name
	-1 for false.

	parameter *cmdln - the command line.

	returns 1 (true), 0 (false).
*/
int vldsetname(char *cmdln)
{
	int i;
	for (i=0; i<NUM_OF_SETS; i++)
		if (0 == memcmp (cmdln, sets[i], SET_NAME_LEN))
			return (i);
	return (-1);
}


/*
	vldnum - validate number

	This function determines if the first token in the given string
	is a valid number (an int, 0-127 inc.). 1=digit, 2=two-digit, 
	3=three-digit number. 0=false.
	If -1 is the token, then -1 is returned.

	parameter *cmdln - the command line

	return: 1 if valid number in range.
			0 if invalid.
		   -1 if -1
*/
int vldnum(char *cmdln)
{
	char *ptr;
	long num;
	
	num = strtol(cmdln, &ptr, BASE);

	if (num == -1)
		return (-1);
	if (1 <= num && num <= 9)
		return (1);
	if (10 <= num && num <= 99)
		return (2);
	if (100 <= num && num <= 127)
		return (3);
	if (num < 0 || 127 < num)
		errmsg(2);
	if (num == 0)
	{
		/**/
		if (*cmdln == '0')
		{
			return (1);
		}
		else
		{
			errmsg(4);
		}
	}

	return (0);
}

/*
	errmsg - Error message function

	description: gets a flag number to represent the error
				and prints the appropriate error to terminal
	
	parameter: int err - the error number to be printed
*/
void errmsg(int err)
{
	switch (err)
	{
		case 0:
			printf("Undefined set name\n");
			break;
		case 1:
			printf("Undefined command name\n");
			break;
		case 2:
			printf("Invalid set member - value out of range\n");
			break;
		case 3:
			printf("List of set members is not terminated correctly\n");
			break;
		case 4:
			printf("Invalid set member - not an integer\n");
			break;
		case 5:
			printf("Missing parameter\n");
			break;
		case 6:
			printf("Extraneous text after end of command\n");
			break;  
		case 7:
			printf("Multiple consecutive comma\n");
			break;
		case 8:
			printf("Missing comma\n");
			break;
		case 9:
			printf("Illegal comma\n");
			break;
		case 10:
			printf("Undefined set name parameter 2\n");
			break;
		default:
			printf("default error message\n");
			break;
	}
}

/*
	execmd - execute command.

	This function gets a command line and executes it
	accordingly. It assumes the command line input is valid.

	parameter *cmdln - command line string.
*/
#ifdef BLA
void execmd(char *cmdln)
{
	int command;
	int num_array[MAX_ARR_SIZE];

	command = vldcmdname(cmdln);
	switch (command)
	{
		/* read_set */
		case 0:

			cmdln += strlen(commands[command]);
			while (isspace(*cmdln))
				++cmdln;
			

			read_set(set1, num_array);
			break;
		default:
			break;
			}
}
#endif
