#include "minishell.h"

int	crash_cd(t_dlist *cmd, t_shell *crash)
{
	char	*path;
	uint8_t	arg_counter;
	
	arg_counter = 0;
	while (cmd->arg[arg_counter])
	{
		if (arg_counter++ > 1)
		{
			putstr_fd("crash: cd: too many arguments\n", STDERR_FILENO);
			return (RETURN_FAILURE);
		}
	}
	if (cmd->arg[1])
		path = cmd->arg[1];
	else
		path = getenv("HOME"); /* FIXME crash_getenv() */
	if (chdir(path) < 0)
	{
		print_errno("crash");
		return (RETURN_FAILURE);
	}
	else 
		return (RETURN_SUCCESS);
	(void)crash;
}
