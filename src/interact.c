#include "minishell.h"

int	interact(t_shell *crash)
{
	char *line;

	while (1)
	{
		line = crash_readline(crash);
		printf("%*s\n",(int)strlen(crash->prompt)+(int)strlen(line), line);
	}
}
