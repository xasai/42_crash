#include "history.h"

void	remove_extra_tails(t_lsthead *lsthead)
{
	t_histlst	*prev;
	t_histlst	*tail;

	if (!lsthead)
		 return ;
	while (lsthead->size > HISTSIZE)
	{
		tail = lsthead->tail;
		prev = tail->prev;
		free(tail->line);
		free(tail);
		lsthead->tail = prev;
		lsthead->size--;
	}
}

void	push_list(t_lsthead *lsthead, char *str)
{
	t_histlst *new;	
	t_histlst *head;

	new = init_histlst(str);
	if (!new)
		exit_message("Allocation of memory failure", SYS_ERROR);
	if (lsthead->head)
	{
		head = lsthead->head;
		head->prev = new;
		new->next = head;
		lsthead->head = new;
	}
	else
		*lsthead = (t_lsthead){.head = new, .tail = new, .size = 0};
	lsthead->size++;
}

t_histlst *init_histlst(char *line)
{
	t_histlst	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	*new = (t_histlst){.line = line, 0};
	return (new);
}
