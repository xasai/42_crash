#include "minishell.h"

#define SHOW_DEBUG 0
/*
*==============================================================================
** DESCRIPTION:
**	Iterate on builtin's names list and compare it to cmdname.
**	If found equal, return index of builtin.
**	Otherwise return 0.
*/
static int8_t	is_builtin(char *cmdname)
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
		else
			DEBUG("DOESNT match cmd '%s' builtin '%s'\n", cmdname, name);
		idx++;
	}
	return (-1);
}

/*
*==============================================================================
** DESCRIPTION:
**	Check if cmd->name is in builtin list and execute this builtin
**	if it is there. And then return 1.
**	Otherwise return 0.
*/
bool	builtin_exec(t_cmdlst *cmd)
{
	int8_t		builtin_idx;	
	static	uint8_t	(*builtin_func[])(t_cmdlst *) = \
	{echo_builtin, cd_builtin, pwd_builtin, env_builtin,
	export_builtin, unset_builtin, 	exit_builtin};

	builtin_idx = is_builtin(cmd->name);
	if (builtin_idx >= 0)
	{
		g_sh->exit_status = (*builtin_func[builtin_idx])(cmd);
		return (1);
	}
	else 
		return (0);
}
