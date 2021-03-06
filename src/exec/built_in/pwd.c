#include "minishell.h"

uint8_t	pwd_builtin(t_cmdlst *cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit_message("Memory allocation Failure", SYS_ERROR);
	putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
	(void)cmd;
}
