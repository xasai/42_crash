#include "readline.h"

/*
** DESCRIPTION:
** 		This function allocates one node of t_chrlst linked list.
**		Assigns its chr field to chr.
**		Assigns both prev and next pointers to NULL.
** RETURN VALUE
**		NEW_NODE:	if allocation succeed.
**		NULL:		if allocation fails.
*/
t_chrlst	*init_chrlst(char chr)
{
	t_chrlst	*new_node;
	
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->chr = chr;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
