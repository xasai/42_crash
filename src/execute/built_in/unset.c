#include "minishell.h"

#define SHOW_DEBUG 0

uint8_t	unset_builtin(t_cmdlst *cmd)
{
	int		env_idx;
	size_t	arg_idx;

	arg_idx = 1;
	while (cmd->arg[arg_idx])
	{
		env_idx = getenv_idx(cmd->arg[arg_idx]);
		if (env_idx >= 0)
		{
			DEBUG("NAME %s\n", cmd->arg[arg_idx]);
			crash_unsetenv(cmd->arg[arg_idx]);
			if (!ft_strncmp(cmd->arg[arg_idx], "PATH", 5))
				rebuild_path();
		}
		arg_idx++;
	}
	return (EXIT_SUCCESS);
}
