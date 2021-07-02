#include "minishell.h"

uint8_t	echo_builtin(t_cmdlst *cmd)
{
	bool	nl;
	size_t	arg_index;

	nl = true;
	arg_index = 1;
	if (cmd->args[1] && !ft_strncmp(cmd->args[1], "-n", 3))
	{	
		nl = false;
		arg_index++;
	}
	while (cmd->args[arg_index])
	{
		putstr_fd(cmd->args[arg_index], STDOUT_FILENO);
		arg_index++;
		if (cmd->args[arg_index])
			putchar_fd(' ', STDOUT_FILENO);
	}
	if (nl)
		putchar_fd('\n', STDOUT_FILENO);
	return (RETURN_SUCCESS);
	(void)g_sh;
}
