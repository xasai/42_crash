#include "minishell.h"

static uint8_t	is_builtin(char *cmdname)
{
	size_t		idx;
	size_t		cmdlen;
	char const	*name;
	const char	*names[] = {"echo", "cd", "pwd", "env", \
							"export", "unset", "exit", NULL};

	idx = 0;
	cmdlen = ft_strlen(cmdname);
	while (names[idx])
	{
		name = names[idx];
		if (!ft_strncmp(cmdname, name, cmdlen))
			return (idx);
		idx++;
	}
	return (0);
}

int	builtin_exec(t_dlist *cmd, t_shell *crash)
{
	uint8_t	builtin_idx;	
	static int (*builtin_func[2])(t_dlist *, t_shell *) = {crash_echo, 0};
	
	builtin_idx = is_builtin(cmd->name);
	if (builtin_idx)
	{
		(*builtin_func[builtin_idx])(cmd, crash);
		return (1);
	}
	else 
		return (0);
}
