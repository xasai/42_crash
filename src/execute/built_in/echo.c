#include "minishell.h"

int	echo_builtin(t_dlist *cmd, t_shell *crash)
{
	bool	nl;
	char	*arg_value;
	size_t	arg_index;

	nl = true;
	arg_index = 1;
	arg_value = cmd->arg[arg_index];
	if (ft_strncmp(arg_value, "-n", 3))
	{	
		nl = false;
		arg_index++;
	}
	while (cmd->arg[arg_index])
	{
		arg_value = cmd->arg[arg_index];
		putstr_fd(arg_value, STDOUT_FILENO);
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (RETURN_SUCCESS);
	(void)crash;
}
