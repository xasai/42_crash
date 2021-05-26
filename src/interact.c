#include "minishell.h"

int	interact(void)
{
	char *line;

	while (1)
	{
		line = readline("crash$: ");
		/* Here parsing starts */
		//ft_putendl_fd(line, STDOUT_FILENO);
		(void)line;
	}
}
