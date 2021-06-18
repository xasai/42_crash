#include "minishell.h"

int	interact(t_shell *crash)
{
	char *line;
	t_dlist *cmd;

	while (true)
	{
		line = crash_readline(crash);
		if (*line)
		{
			cmd = ft_line_analyz(line);
			cmdline_exec(cmd , crash);
			print_this_shit(cmd);
		}
		//printf("%*s\n",(int)strlen(crash->prompt)+(int)strlen(line), line);
	}
}
