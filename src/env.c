#include "minishell.h"

int	getenv_idx(char *name, char **envp)	
{
	size_t	env_idx;
	size_t	name_len;

	env_idx = 0;
	name_len = ft_strlen(name);
	while (envp[env_idx])
	{
		if (!ft_strncmp(envp[env_idx], name, name_len)
			&& envp[env_idx][name_len] == '=')
			return (env_idx);
		env_idx++;
	}
	return (-1);
}

char	*crash_getenv_ptr(char *name, char **envp)
{	
	size_t	env_idx;
	size_t	name_len;

	env_idx = 0;
	name_len = ft_strlen(name);
	while (envp[env_idx])
	{
		if (!ft_strncmp(envp[env_idx], name, name_len)
			&& envp[env_idx][name_len] == '=')
			return (envp[env_idx]);
		env_idx++;
	}
	return (NULL);
}

char	*crash_getenv(char *name, char **envp)
{
	char *varp;

	varp = crash_getenv_ptr(name, envp);
	if (!varp)
		return (NULL);
	varp = ft_strchr(varp, '=');
	return (++varp);
}
