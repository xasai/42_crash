#include "minishell.h"

static void	change_value(char *name, char *value, int idx)
{
	free(g_sh->envp[idx]);
	g_sh->envp[idx] = cat_lines_tab((char *[4]){name, "=", value, NULL});
	if (!g_sh->envp[idx])
		exit_message("Memory allocation failure", SYS_ERROR);
}

void	crash_setenv(char *name, char *value)
{
	int		idx;
	size_t	size;
	char	**new_envp;

	size = 0;
	idx = getenv_idx(name);
	if (idx >= 0)
	{
		change_value(name, value, idx);
		return ;
	}
	while (g_sh->envp[size++] != NULL)
		;
	new_envp = ft_calloc(sizeof(*new_envp), (size + 1));
	if (!new_envp)
		exit_message("Memory allocation failure", SYS_ERROR);
	idx = -1;
	while (g_sh->envp[++idx])
		new_envp[idx] = g_sh->envp[idx];
	new_envp[idx] = cat_lines_tab((char *[4]){name, "=", value, NULL});
	if (!new_envp[idx])
		exit_message("Memory allocation failure", SYS_ERROR);
	free(g_sh->envp);
	g_sh->envp = new_envp;
}
