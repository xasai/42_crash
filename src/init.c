#include "minishell.h"


/*
** DESCRIPTION:
**	Initializing struct s_shell in this function.
*/
t_shell *init_term(char **envp)
{
	
	t_shell	*s_shell;
	
	s_shell = malloc(sizeof(*s_shell));
	if (NULL == s_shell)
		exit_message("Malloc Error init.c:7\n", SYS_ERROR);
	s_shell->envp = envp;
	s_shell->hist = init_history();
	return (s_shell);
}
