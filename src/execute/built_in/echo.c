#include "minishell.h"

int	echo_builtin(t_cmdlst *cmd, t_shell *crash)
{
	bool	nl;
	size_t	arg_index;

	nl = true;
	arg_index = 1;
	if (cmd->arg[1] && !ft_strncmp(cmd->arg[1], "-n", 3))
	{	
		nl = false;
		arg_index++;
	}
	while (cmd->arg[arg_index])
	{
		putstr_fd(cmd->arg[arg_index], STDOUT_FILENO);
		arg_index++;
		if (cmd->arg[arg_index])
			putchar_fd(' ', STDOUT_FILENO);
	}
	if (nl)
		putchar_fd('\n', STDOUT_FILENO);
	return (RETURN_SUCCESS);
	(void)crash;
}
