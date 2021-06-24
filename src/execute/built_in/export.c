#include "minishell.h"

static bool is_valid_name(char *name)
{
	size_t	i;
	
	i = 0;
	if (ft_isalpha(name[i]) || name[i] == '_')
	{
		i++;
		while (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		if (name[i] == '=')
			return (true);
	}
	putstr_fd("crash: export: '", STDERR_FILENO);
	putstr_fd(name, STDERR_FILENO);
	putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (false);
}

uint8_t	export_builtin(t_cmdlst *cmd)
{	
	char	**argp;
	char	*env_value;
	char	*env_name;
	uint8_t	ret;
	
	ret = RETURN_SUCCESS;
	argp = cmd->arg + 1;
	if (NULL == *argp)
		return (env_builtin(cmd));
	while (*argp)
	{
		if (is_valid_name(*argp))
		{
			env_name = getenv_name(*argp);
			env_value = ft_strchr(*argp, '=') + 1;
			crash_setenv(env_name, env_value);
			if ((*argp)[4] == '=' && ft_strncmp(env_name, "PATH", 4)) 
				rebuild_path();
			free(env_name);
		}
		else
			ret = RETURN_FAILURE;
		argp++;
	}
	return (ret);
}
/*
int	export_builtin(t_cmdlst *cmd)
{	
	char	**args;
	char	*env_value;
	char	*env_name;
	size_t	idx;
	uint8_t	ret;
	
	ret = RETURN_SUCCESS;
	idx = 1;
	args = cmd->arg;
	if (NULL == args[idx])
		return (env_builtin(cmd));
	while (args[idx])
	{
		if (is_valid_name(args[idx]))
		{
			env_name = getenv_name(args[idx]);
			env_value = ft_strchr(args[idx], '=') + 1;
			crash_setenv(env_name, env_value);
			if (args[idx][4] == '=' && ft_strncmp(env_name, "PATH", 4)) 
				rebuild_path();
			free(env_name);
		}
		else
			ret = RETURN_FAILURE;
		idx++;
	}
	return (ret);
}*/
