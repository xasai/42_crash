#include "minishell.h"

#define SHOW_DEBUG 0

/*
**=================================================
** DESCRIPTION:
**	rebuild_path will be called each time user change $PATH variable
**	and will clear our old **char array of paths and change it with
**	new array of strings spliting $PATH value by ':' semicolon.
*/
void	rebuild_path(void)
{
	char	*env_path;

	DEBUG("Rebuilding path\n");
	free_tab((void *)g_sh->path);
	env_path = crash_getenv("PATH");
	if (!env_path)
		return ;
	g_sh->path = ft_split(env_path, ':');
}
