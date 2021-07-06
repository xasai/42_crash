#include "minishell.h"

uint8_t	_error(char *message)
{
	putstr_fd("crash: cd: ", STDERR_FILENO);
	putendl_fd(message, STDERR_FILENO);
	return (RETURN_FAILURE);
}

uint8_t	cd_builtin(t_cmdlst *cmd)
{
	char	*path;

	path = cmd->args[1];
	if (path && cmd->args[2])
		return (_error("too many arguments"));
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
	{
		path = crash_getenv("HOME");
		if (!path)
		{
			putstr_fd("crash: cd: HOME not set\n", STDOUT_FILENO);
			return (RETURN_FAILURE);
		}
	}
	if (chdir(path) < 0)
	{
		print_errno(path);	
		putchar_fd('\n', STDERR_FILENO);
	}
	return (RETURN_SUCCESS);
}
