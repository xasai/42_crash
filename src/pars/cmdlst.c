#include "minishell.h"

t_cmdlst	*new_cmdlst(t_cmdlst *curr)
{
	t_cmdlst	*new_l;

	new_l = malloc(sizeof(t_cmdlst));
	if (!new_l)
		exit_message("Memory allocation failure", SYS_ERROR);
	*new_l = (t_cmdlst){.prev = curr};
	if (curr)
		curr->next = new_l;
	return (new_l);
}

void	cmdlst_free(t_cmdlst *cmdl)
{
	t_cmdlst	*next;

	while (cmdl)
	{
		next = cmdl->next;
		free(cmdl->pathname);
		free_tab((void *)cmdl->args);
		redir_lst_free(cmdl->rlst);
		free(cmdl);
		cmdl = next;
	}
}
