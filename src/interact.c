#include "minishell.h"

int	interact(t_shell *crash)
{
	char *line;
	t_cmdlst *cmd;

	while (true)
	{
		line = crash_readline(crash);
		if (*line)
		{
			cmd = ft_line_analyz(line, crash);
			cmdline_exec(cmd , crash);
			print_this_shit(cmd);
		}
		//printf("%*s\n",(int)strlen(crash->prompt)+(int)strlen(line), line);
	}
}
