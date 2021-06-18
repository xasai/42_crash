#include "minishell.h"

/*
*==============================================================================
** DESCRIPTION:
**	Iterate on builtin's names list and compare it to cmdname.
**	If found equal, return index of builtin.
**	Otherwise return 0.
*/
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
		if (!ft_strncmp(cmdname, name, cmdlen + 1))
			return (idx);
		idx++;
	}
	return (0);
}

/*
*==============================================================================
** DESCRIPTION:
**	Check if cmd->name is in builtin list and execute this builtin
**	if it is there. And then return 1.
**	Otherwise return 0.
*/
bool	builtin_exec(t_dlist *cmd, t_shell *crash)
{
	uint8_t		builtin_idx;	
	static	int	(*builtin_func[])(t_dlist *, t_shell *) = \
	{echo_builtin, cd_builtin, pwd_builtin, env_builtin,
	export_builtin, unset_builtin, 	exit_builtin};

	builtin_idx = is_builtin(cmd->name);
	if (builtin_idx)
	{
		(*builtin_func[builtin_idx])(cmd, crash);
		return (1);
	}
	else
		return (0);
}
