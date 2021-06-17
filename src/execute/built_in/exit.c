#include "minishell.h"

static bool	is_numeric_arg(char *arg)
{
	while (ft_isspace(*arg))
		arg++;
	while (ft_isdigit(*arg))
		arg++;
	while (ft_isspace(*arg))
		arg++;
	return (*arg == '\0');
}

int	exit_builtin(t_dlist *cmd, t_shell *crash)
{
	char	*arg;
	int		exit_code;

	exit_code = 0; // FIXME assign to crash->status_code 
	arg = cmd->arg[1];
	if (arg)
	{
		if (!is_numeric_arg(arg))
		{
			putstr_fd("crash: exit: ", STDERR_FILENO);
			putstr_fd(arg, STDERR_FILENO);
			exit_message(": numeric argument required", BUILTIN_ERROR);
		}		
		if (cmd->arg[2])
		{
			putstr_fd("crash: exit: too many arguments\n", STDERR_FILENO);
			return (BUILTIN_ERROR);
		}		
		exit_code = ft_atoi(cmd->arg[1]);
	}
	exit_message("exit", exit_code);
	return (exit_code);
	(void)crash;
}
