#include "minishell.h"

int	interact(void)
{
	char *line;
	t_cmdlst *cmd;

	while (true)
	{
		line = crash_readline();
		if (*line)
		{
			cmd = ft_line_analyz(line);
			cmdline_exec(cmd);
			print_this_shit(cmd);
		}
	}
}
