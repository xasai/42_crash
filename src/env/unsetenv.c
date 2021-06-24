#include "minishell.h"

void	crash_unsetenv(char *name)
{
	int		rm_idx;
	int		new_idx;
	int		old_idx;
	char	**new_envp;

	rm_idx = getenv_idx(name);
	if (rm_idx < 0)
		return ;
	old_idx = 0;
	while (g_sh->envp[old_idx++])
		;
	new_envp = ft_calloc(sizeof(*new_envp), old_idx - 1);
	if (!new_envp)
		exit_message("Memory allocation failure", 1);
	new_idx = 0;
	old_idx = 0;
	while (old_idx < rm_idx)
		new_envp[new_idx++] = g_sh->envp[old_idx++];	
	old_idx++;
	while (g_sh->envp[old_idx])
		new_envp[new_idx++] = g_sh->envp[old_idx++];	
	free(g_sh->envp[rm_idx]);
	free(g_sh->envp);
	g_sh->envp = new_envp;
}
