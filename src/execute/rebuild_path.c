#include "minishell.h"

void rebuild_path(t_shell *crash)
{
	char *env_path;
	
	free_tab((void *)crash->path);	
	env_path = crash_getenv("PATH", crash->envp);
	if (!env_path)
		return ;	
	crash->path = ft_split(env_path, ':');
	free(env_path);
}
