#include "minishell.h"

t_terminfo	*g_term;

void	init_first(int ac, char **av, char **envp)
{
	g_term = malloc(sizeof(*g_term));
	if (NULL == g_term)
		exit_message("Malloc Error init.c:7\n", 1);
	g_term->envp = envp;
	term_capability_data_init();
	g_term->termios = termios_init();
	(void)ac;
	(void)av;
}

void	term_capability_data_init(void)
{
	char		*term_type;
	int			success;

	term_type = getenv("TERM");
	if (0 == term_type)
	{
		exit_message("Specify terminal type within env variable 'TERM'", 1);
	}
	success = tgetent(NULL, term_type);
	if (success < 0)
	{
		exit_message("Could not access termcap database", 1);
	}
	else if (!success)
	{
		exit_message("Your terminal type is not defined", 1);
	}
}

struct termios termios_init(void)
{
	struct termios	termios;
	int				success;	
	
	success = tcgetattr(STDIN_FILENO, &termios);
	if (success < 0)	
		exit_message("Could not get interface attributes", 1);
	termios.c_lflag &= ~(ICANON);
	success = tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	if (success < 0)
		exit_message("Could not set interface attributes", 1);
	return (termios);
}
