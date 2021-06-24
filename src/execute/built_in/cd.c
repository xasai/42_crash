#include "minishell.h"

/* FIXME g_sh_getenv()
check if HOME exist
and print mess if not*/

uint8_t	cd_builtin(t_cmdlst *cmd)
{
	char	*path;

	path = cmd->arg[1];
	if (path && cmd->arg[2])
	{
		putstr_fd("g_sh: cd: too many arguments\n", STDERR_FILENO);
		return (RETURN_FAILURE);
	}
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
	{
		path = crash_getenv("HOME");
		if (!path)
		{
			putstr_fd("g_sh: cd: HOME not set\n", STDERR_FILENO);
			return (RETURN_FAILURE);
		}
	}
	if (chdir(path) < 0)
	{
		print_errno("g_sh");
		return (RETURN_FAILURE);
	}
	else
		return (RETURN_SUCCESS);
}
