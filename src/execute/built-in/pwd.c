#include "minishell.h"

int	crash_pwd(t_dlist *cmd, t_shell *crash)
{
	char	*cwd;
	
	cwd = _getcwd();
	if (!cwd)
		exit_message("Memory allocation Failure", SYS_ERROR);
	putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
	(void)cmd;
	(void)crash;
}
