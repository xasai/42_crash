#include "minishell.h"

int	getenv_idx(char *name)	
{
	char	**envp;
	size_t	env_idx;
	size_t	name_len;

	env_idx = 0;
	envp = g_sh->envp;
	name_len = ft_strlen(name);
	while (g_sh->envp[env_idx])
	{
		if (!ft_strncmp(envp[env_idx], name, name_len)
			&& envp[env_idx][name_len] == '=')
			return (env_idx);
		env_idx++;
	}
	return (-1);
}
