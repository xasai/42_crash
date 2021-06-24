#include "minishell.h"

char	*crash_getenv(char *name)
{
	char	*var_p;
	int		var_i;

	var_i = getenv_idx(name);
	if (var_i < 0)
		return (NULL);
	var_p = ft_strchr(g_sh->envp[var_i], '=') + 1; // TODO CHECk + 1 works
	return (var_p);
}
