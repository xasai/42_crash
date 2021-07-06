#include "minishell.h"

static t_redir_lst	*new_rlst(char type)
{
	t_redir_lst	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	*new = (t_redir_lst){.type = type};
	return (new);
}

t_redir_lst	*append_rlst(t_redir_lst **head, char type)
{
	t_redir_lst	*new;
	t_redir_lst	*cur_rlst;

	new = new_rlst(type);
	if (NULL == new)
		exit_message("Memory allocation failure", SYS_ERROR);
	if (!*head)
		*head = new;
	else
	{
		cur_rlst = *head;
		while (cur_rlst->next != NULL)
			cur_rlst = cur_rlst->next;
		cur_rlst->next = new;
	}
	return (new);
}

void	redir_lst_free(t_redir_lst *head)
{
	t_redir_lst	*next;

	while (head)
	{
		next = head->next;
		if (head->type == '-')
			unlink(head->filename);
		free(head->filename);
		free(head);
		head = next;
	}
}
