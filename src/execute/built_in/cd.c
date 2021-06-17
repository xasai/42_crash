#include "minishell.h"

/* FIXME crash_getenv()
check if HOME exist
and print mess if not*/

int	cd_builtin(t_dlist *cmd, t_shell *crash)
{
	char	*path;

	path = cmd->arg[1];
	if (cmd->arg[2])
	{
		putstr_fd("crash: cd: too many arguments\n", STDERR_FILENO);
		return (RETURN_FAILURE);
	}
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
	{
		path = getenv("HOME");
	}
	if (chdir(path) < 0)
	{
		print_errno("crash");
		return (RETURN_FAILURE);
	}
	else
		return (RETURN_SUCCESS);
	(void)crash;
}
