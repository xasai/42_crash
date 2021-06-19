#include "minishell.h"

/* FIXME crash_getenv()
check if HOME exist
and print mess if not*/

int	cd_builtin(t_cmdlst *cmd, t_shell *crash)
{
	char	*path;

	path = cmd->arg[1];
	if (path && cmd->arg[2])
	{
		putstr_fd("crash: cd: too many arguments\n", STDERR_FILENO);
		return (RETURN_FAILURE);
	}
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
	{
		path = crash_getenv("HOME", crash->envp);
		if (!path)
		{
			putstr_fd("crash: cd: HOME not set\n", STDERR_FILENO);
			return (RETURN_FAILURE);
		}
	}
	if (chdir(path) < 0)
	{
		print_errno("crash");
		return (RETURN_FAILURE);
	}
	else
		return (RETURN_SUCCESS);
}
