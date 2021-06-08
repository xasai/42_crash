#include "minishell.h"

int	interact(t_shell *s_shell)
{
	char *line;

	while (1)
	{
		line = readline("crash$: ", s_shell->hist);
		printf("\nline   |%s|\n", line);
		(void)line;
	}
}
