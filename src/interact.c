#include "minishell.h"

#define SHOW_DEBUG 0
/*
**=================================================
** DESCRIPTION:
**	interact() is a main life cycle of crash shell.
**	How cycle works:
**		1) Read line from user input.
**		2) Parse this line in linked list t_cmdlst.
**		3) Execute all commands from t_cmdlst linked list.
*/
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
			if (SHOW_DEBUG)
				print_this_shit(cmd);
			cmdlst_free(cmd);
		}
	}
	return (EXIT_SUCCESS);
}
