#include "minishell.h"

int	exit_builtin(t_dlist *cmd, t_shell *crash)
{
	int exit_code;

	exit_code = 0;
	if (cmd->arg[2])
	{
		putstr_fd("crash: exit: too may arguments\n", STDERR_FILENO);
		return (BUILTIN_ERROR);
	}
	if (cmd->arg[1]) 
		exit_code = ft_atoi(cmd->arg[1]);
		/* also should check for only [0-9] sequence */
	exit_message("exit", exit_code);
	return (exit_code);
	(void)crash;
}
