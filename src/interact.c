#include "minishell.h"

int	interact(void)
{
	char *line;

	while (1)
	{
		line = readline("crash$: ");
		printf("\nline   |%s|\n", line);
		(void)line;
	}
}
