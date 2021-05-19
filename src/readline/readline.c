#include "minishell.h"

char *readline(const char *prompt)
{
	char	*line;	

	write(1, prompt, ft_strlen(prompt));
	if (get_next_line(STDIN_FILENO, &line) < 0)
		exit_message("Somethig went wrong while reading from STDIN", 1);
	return (line);
}

int	interact(void)
{
	char *line;

	while (1)
	{
		line = readline("crash$: ");
		/* Here parsing starts */
		(void)line;
	}
}
