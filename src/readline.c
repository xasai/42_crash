#include "minishell.h"

#define SHOW_DEBUG 0

static	void	_int_handler(int signum)
{
	signal(signum, _int_handler);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sh->exit_status = 0x80 + signum;
}

static	void	_set_sighandlers(void)
{
	signal(SIGINT, _int_handler);
	signal(SIGQUIT, SIG_IGN);
}

static	void	_set_sigdefault(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

char	*crash_readline(void)
{
	char		*line;
	size_t		len;
	static char	*prev_line = "";

	_set_sigdefault();
	_set_sighandlers();
	line = readline(g_sh->prompt);
	if (line == NULL)
		exit_message("exit", EXIT_SUCCESS);
	len = ft_strlen(line);
	if (len && ft_strncmp(line, prev_line, len + 1))
		add_history(line);
	if (*prev_line != '\0')
		free(prev_line);
	prev_line = line;
	return (line);
}
