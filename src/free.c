#include "minishell.h"

void	redirlst_free(void)
{
	/*
	void	*next;

	while (rlst) 	
	{
		next = rlst->next;
		free(rlst->name);
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
		free(cmdl->name);
		if (cmdl->arg)
			free_tab((void *)cmdl->arg);
		//if (cmdl->redirlst != NULL)
		//	redirlst_free(cmdl->redirlst;
		free(cmdl);
		cmdl = next;
	}
}
