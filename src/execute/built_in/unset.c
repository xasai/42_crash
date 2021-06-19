#include "minishell.h"

static char **unset_env(char *env, char **envp)
{
	size_t	new_idx;
	size_t	old_idx;
	size_t	new_size;
	char	**new_envp;
	
	new_size = 0;
	while (envp[new_size])
		new_size++;	
	new_envp = ft_calloc(sizeof(*new_envp), (new_size));	
	if (!new_envp)
		exit_message("Memory allocation failure", SYS_ERROR);
	new_idx = 0;
	old_idx = 0;
	while (envp[old_idx])
	{
		if (envp[old_idx] == env)
			old_idx++;
		new_envp[new_idx] = envp[old_idx];
		new_idx++;	
		old_idx++;
	}
	free(env);
	free(envp);
	return (new_envp);
}

int	unset_builtin(t_cmdlst *cmd, t_shell *crash)
{
	char	*var;
	size_t	arg_idx;

	arg_idx = 1;
	while (cmd->arg[arg_idx])
	{
		var = crash_getenv_ptr(cmd->arg[arg_idx], crash->envp);
		if (var)
		{
			crash->envp = unset_env(var, crash->envp);
			if (ft_strncmp(var, "PATH", 5))
				rebuild_path(crash);	
		}
		arg_idx++;	
	}
	return (EXIT_SUCCESS);
}
