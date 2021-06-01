#include "minishell.h"


t_shell *g_shell;

/*
** DESCRIPTION:
**	
*/
void	init_term(char **envp)
{
	g_shell = malloc(sizeof(*g_shell));
	if (NULL == g_shell)
		exit_message("Malloc Error init.c:7\n", EXIT_FAILURE);
	g_shell->envp = envp;
}
