#include "minishell.h"

char *readline(const char *prompt)
{
	char	buf[2];	
	char	*line;
	ssize_t	size;
	
			
	line = NULL;
	size = 1;
	write(1, prompt, ft_strlen(prompt));
	while (size > 0)
	{
		read(STDIN_FILENO, buf, 2);
		if (size == -1 || ft_strchr(buf, '\n'))
			break ;	
	}
	if (size == -1)
	{
		free(line);
		exit_message("In function readline() ", 1);
	}
	return (line);
}
