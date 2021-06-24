#include "minishell.h"

int	interact(t_shell *sh)
{
	char *line;
	t_cmdlst *cmd;

	while (true)
	{
		line = crash_readline(sh);
		if (*line)
		{
			cmd = ft_line_analyz(line, sh);
			cmdline_exec(cmd , sh);
			print_this_shit(cmd);
		}
		//printf("%*s\n",(int)strlen(sh->prompt)+(int)strlen(line), line);
	}
}
