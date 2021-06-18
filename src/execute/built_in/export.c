#include "minishell.h"

static bool is_valid_name(char *name)
{
	if (!ft_isalpha(*name) && *name++ != '_')
		return (false);
	while (!ft_isalnum(*name) || *name == '_')
		name++;
	if (*name == '=')
		return (true);
	return (false);
}

static void print_error_syntax(char *name)
{
	putstr_fd("crash: export: '", STDERR_FILENO);
	putstr_fd(name, STDERR_FILENO);
	putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static char **env_realloc(char **envp, size_t addsize)
{
	size_t	idx;
	size_t	size;
	char	**new_env;

	if (!addsize)
		return (envp);
	size = 0;
	while (envp[size++])
		;
	size += addsize;
	new_env = ft_calloc(sizeof(*new_env), size);	
	if (!new_env)
		exit_message("Memory allocation failure", SYS_ERROR);
	idx = 0;
	while (envp[idx])
	{
		new_env[idx] = envp[idx];
		idx++;
	}
	free(envp);
	return (new_env);
}

static void append_env(char **args, t_shell *crash)
{
	size_t	arg_idx;
	size_t	env_idx;
	size_t	count_to_add;
	
	arg_idx = 1;
	count_to_add = 0;
	while (args[arg_idx])
	{
		if (is_valid_name(args[arg_idx]))
			count_to_add++;	
		else
			print_error_syntax(args[arg_idx]);
		arg_idx++;
	}
	crash->envp = env_realloc(crash->envp, count_to_add);	
	env_idx = 0;
	while (crash->envp[env_idx])	
		env_idx++;
	arg_idx = 0;
	while (args[arg_idx])
	{
		if (is_valid_name(args[arg_idx]))
			crash->envp[env_idx] = args[arg_idx];
		env_idx++;
		arg_idx++;
	}
}

int	export_builtin(t_dlist *cmd, t_shell *crash)
{
	if (cmd->arg[1])
		append_env(cmd->arg, crash);
	else
		env_builtin(cmd, crash);		
	return (RETURN_SUCCESS);
}
