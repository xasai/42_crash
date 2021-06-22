#include "minishell.h"

void rebuild_path()
{
	char *env_path;
	
	free_tab((void *)g_sh->path);	
	env_path = crash_getenv("PATH", g_sh->envp);
	if (!env_path)
		return ;	
	g_sh->path = ft_split(env_path, ':');
	free(env_path);
}
