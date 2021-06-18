#include "minishell.h"
#define MAX_NAME_LEN 1024

static bool is_valid_name(char *name)
{
	if (!ft_isalpha(*name) && *name++ != '_')
		return (false);
	while (!ft_isalnum(*name) || *name == '_')
		name++;
	if (*name == '=')
		return (true);
	putstr_fd("crash: export: '", STDERR_FILENO);
	putstr_fd(name, STDERR_FILENO);
	putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (false);
}

static bool	swap_if_exist(char *var, char **envp)
{
	size_t	len;	
	int		oldvar_idx;	
	char	name[MAX_NAME_LEN];
	
	len = 0;
	while (var[len] != '=')
		len++;
	ft_strlcpy(name, var, len);
	oldvar_idx = getenv_idx(name, envp);
	if (oldvar_idx > -1)
	{
		free(envp[oldvar_idx]);
		envp[oldvar_idx] = ft_strdup(var);
		if (!envp[oldvar_idx])
			exit_message("Memory allocation failure", SYS_ERROR);
		return (true);
	}
	return (false);
}

static char **append_var(char *var, char **old_envp)
{
	size_t	idx;
	size_t	size;
	char	**new_envp;

	if (swap_if_exist(var, old_envp))
		return (old_envp);
	size = 0;
	while (old_envp[size++] != NULL)
		;
	new_envp = ft_calloc(sizeof(*new_envp), (size + 1));
	if (!new_envp)
		exit_message("Memory allocation failure", SYS_ERROR);
	idx = 0;
	while (old_envp[idx])
	{
		new_envp[idx] = old_envp[idx];
		idx++;
	}
	new_envp[idx] = ft_strdup(var);
	if (!new_envp[idx])
		exit_message("Memory allocation failure", SYS_ERROR);
	free(old_envp);
	return (new_envp);
}

int	export_builtin(t_dlist *cmd, t_shell *crash)
{	
	size_t	arg_idx;

	arg_idx = 1;
	if (cmd->arg[arg_idx] == NULL)
		return (env_builtin(cmd, crash));
	while (cmd->arg[arg_idx])
	{
		if (is_valid_name(cmd->arg[arg_idx]))
		{
			crash->envp = append_var(cmd->arg[arg_idx], crash->envp);
			if (cmd->arg[arg_idx][4] == '=' \
			&& ft_strncmp(cmd->arg[arg_idx], "PATH", 4)) 
				rebuild_path(crash);
		}
		arg_idx++;
	}
	return (RETURN_SUCCESS);
}
