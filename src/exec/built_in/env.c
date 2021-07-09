#include "minishell.h"

#define RESET_COLOR "\033[1;0m"

uint8_t	env_builtin(t_cmdlst *cmd)
{
	size_t	idx;
	char	**envp;

	idx = 0;
	envp = g_sh->envp;
	while (envp[idx])
	{
		putendl_fd(envp[idx], STDOUT_FILENO);
		idx++;
	}
	putstr_fd(RESET_COLOR, STDOUT_FILENO);
	return (RETURN_SUCCESS);
	(void)cmd;
}
