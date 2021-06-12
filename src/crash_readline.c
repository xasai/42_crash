#include "minishell.h"

static void _int_handler(int signum)
{
	signal(signum, _int_handler);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	_set_sighandlers(void)
{
	signal(SIGINT, _int_handler);
	signal(SIGQUIT, SIG_IGN); 
}

static void _set_sigdefault(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

char	*crash_readline(t_shell *crash)
{
	char		*line;
	static char	*prev_line = "";
	
	_set_sighandlers();
	line = readline(crash->prompt);
	_set_sigdefault();
	if (line == NULL)
		exit_message("exit", EXIT_SUCCESS);
	if (ft_strncmp(line, prev_line, ft_strlen(line)))
		add_history(line);
	prev_line = line;
	return (line);
}
