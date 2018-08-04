/* labeltable.c */

/* this file implements the label table structure as dynamic linked list */

#include <stdlib.h>
#include <string.h>
#include "datastructures.h"

#define LABELSIZE 64

/* label struct */
struct label
{
	char *name;
	int adress;
	boolean isexternal;
	boolean isincommand;
	
	label *next;
};
/* labels table */
struct labeltable
{
	label *head;
};

void insertlabel(labeltable *lt, label *l)
{
	label *current;
	
	current = lt->head;

	/* if table is empty */
	if (current == NULL)
	{
		lt->head = l; /* define new label as head*/
		return; 	  /* finish */
	}

	/* else, find the last label in list and point to new label as next*/
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = l;
}

void createlabel(labeltable *lt, char *name, int adress, 
				boolean isexternal, boolean isincommand)
{
	/* declare new struct label and malloc */
	label newlabel = malloc(LABELSIZE);
	
	/* copy args to new label */
	strcpy(label.name, name);
	label.adress = adress;
	label.isexternal = isexternal;
	label.isincommand = isincommand;

	/* insert new label to label table*/
	insertlabel(lt, &newlabel);
}

/* if a label with given name exists already in table
	then return true 1
   else
    then return false 0
*/
boolean searchlabel(labeltable *lt, char *name)
{
	label *current;
	boolean isintable = false;

	current = lt->head;
	while (current != null)
	{
		/* if a label with this name exists in table*/
		if (strcmp(name, current.name) == 0)
		{
			isintable = true;
		}

		current = current->next;
	}

	return isintable;
}
