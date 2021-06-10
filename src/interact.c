#include "minishell.h"

int	interact(t_shell *crash)
{
	char *line;

	while (1)
	{
		line = crash_readline(crash);
		ft_line_analyz(line);
		printf("%*s\n",(int)strlen(crash->prompt)+(int)strlen(line), line);
	}
}
