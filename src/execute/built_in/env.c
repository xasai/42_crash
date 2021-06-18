#include "minishell.h"
#define RESET_COLOR "\033[1;0m"

int	env_builtin(t_dlist *cmd, t_shell *crash)
{
	size_t idx;	
	char **envp;
	
	idx = 0;
	envp = crash->envp;
	while (envp[idx])
	{
		putendl_fd(envp[idx], STDOUT_FILENO);
		idx++;
	}
	putstr_fd(RESET_COLOR, STDOUT_FILENO);
	return (RETURN_SUCCESS);
	(void)cmd;
}
