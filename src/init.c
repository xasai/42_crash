#include "minishell.h"


t_shell *g_shell; /* s_shell.h */

/*
** DESCRIPTION:
**	
*/
void	init_term(char **envp)
{
	g_shell = malloc(sizeof(*g_shell));
	if (NULL == g_shell)
		exit_message("Malloc Error init.c:7\n", 1);
	g_shell->envp = envp;
	term_capability_db_init();
	term_capability_data_init();
	if (tcgetattr(STDIN_FILENO, &g_shell->old_termios) < 0)
		exit_message("Could not get interface attributes", 1);
	tputs(g_shell->terminfo.clear, 1, &putint);
}

/*
** DESCRIPTION:
**	
*/
void	term_capability_db_init(void)
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

/*
** DESCRIPTION:
**	
*/
void	term_capability_data_init(void)
{
	struct s_terminfo *ti;	
	char *ks;
	
	ks = tgetstr("ks", NULL);
	tputs(ks, 1, &putint);
	ti = &g_shell->terminfo;
	ti->clear = tgetstr("cl", NULL);
	ti->k_up = tgetstr("ku", NULL);
	ti->k_down = tgetstr("kd", NULL);
	ti->k_left = tgetstr("kl", NULL);
	ti->k_right = tgetstr("kr", NULL);
	ti->k_backspace = tgetstr("kb", NULL);
	ti->move_left = tgetstr("le", NULL);
	ti->move_right = tgetstr("nd", NULL);
	ti->save_c = tgetstr("sc", NULL);
	ti->restore_c = tgetstr("rc", NULL);
	ti->delete_char = tgetstr("dc", NULL);
	/* ce cd */
}

/*
** DESCRIPTION:
**	FIXME FIXME FIXME FIXME 
**	Make this funct switcher
*/
void	termios_init(void)
{
	struct termios	termios;
	int				success;	
	
	termios = g_shell->old_termios;
	termios.c_lflag &= ~(ICANON | ECHO);
	success = tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	if (success < 0)
		exit_message("Could not set interface attributes", 1);
}
