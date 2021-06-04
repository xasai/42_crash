#include "readline.h"

/*
**==================================================================
** DESCRIPTION:
** 		This function allocates one node of t_chrlst linked list.
**		Assigns its chr field to chr.
**		Assigns next to NULL.
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
	*new_node = (t_chrlst){.chr = chr, NULL};
	return (new_node);
}

/*
**==================================================================
** DESCRIPTION:
**		FIXME
*/
void	del_chrlst(t_lsthead *head, size_t index)
{
	t_chrlst	*current;	
	t_chrlst	*prev;
	size_t		i;	

	i = 0;
	prev = NULL;
	current = head->head;
	while (i != index)
	{
		prev = current;
		current = current->next;
		i++;
	}
	if (prev)
		prev->next = current->next;
	else
		head->head = current->next;
	free(current);
	head->size--;
}

/*
**==================================================================
** DESCRIPTION:
**		Frees full chrlst list.	
*/
void	free_chrlst(t_chrlst *head)
{
	t_chrlst	*next;
	
	while (head)
	{
		next = head->next;
		*head  = (t_chrlst){0};
		free(head);
		head = next;
	}
}
/*
**==================================================================
** DESCRIPTION:
**		FIXME
*/
void	insert_chrlst_node(char chr, t_lsthead *head, size_t index)
{
	t_chrlst	*new;
	t_chrlst	*cur;
	size_t		i;

	i = 0;
    new = init_chrlst(chr);
	cur = head->head;
    if (!new)
        exit_message("Malloc failure", EXIT_FAILURE);
    if (index != 0)
    {   
        while (i++ < index - 1)
            cur= cur->next;  
        new->next = cur->next;    
        cur->next = new;
    }
    else
    {   
        new->next = head->head;
        head->head = new;
    }
	head->size++;
}
