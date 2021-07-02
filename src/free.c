#include "minishell.h"

void	redirlst_free(void)
{
	/*
	void	*next;

	while (rlst) 	
	{
		next = rlst->next;
		free(rlst->pathname);
		rlst = next;
	}
	*/
}

void	cmdlst_free(t_cmdlst *cmdl)
{
	t_cmdlst	*next;

	while (cmdl)
	{
		next = cmdl->next;
		free(cmdl->pathname);
		if (cmdl->args)
			free_tab((void *)cmdl->args);
		free(cmdl);
		cmdl = next;
	}
}
