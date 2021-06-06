#include "minishell.h"


static t_shell *g_shell;

/*
** DESCRIPTION:
**	Initializing struct g_shell in this function.
*/
void	init_term(char **envp)
{
	g_shell = malloc(sizeof(*g_shell));
	if (NULL == g_shell)
		exit_message("Malloc Error init.c:7\n", SYS_ERROR);
	g_shell->envp = envp;
	g_shell->hist = init_history();
}
