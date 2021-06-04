#include "readline.h"

/*
**==================================================================
** DESCRIPTION:
**	Initialize terminal capability database via termcap library.
*/
static void	termcap_init(void)
{
	char		*term_type;
	int			success;

	term_type = getenv("TERM");
	if (0 == term_type)
	{
		exit_message("Specify terminal type within env variable 'TERM'", \
		EXIT_FAILURE);
	}
	success = tgetent(NULL, term_type);
	if (success < 0)
	{
		exit_message("Could not access termcap database", \
		EXIT_FAILURE);
	}
	else if (!success)
	{
		exit_message("Your terminal type is not defined", \
		EXIT_FAILURE);
	}
}

/*
**==================================================================
** DESCRIPTION:
**	On first call of this function, it is initializining all capability
**	we need in struct s_terminfo.
**	Return pointer to that struct
*/
/* ce cd */
struct s_terminfo	*termcap(void)
{
	static bool					initialized;
	static struct s_terminfo	ti;

	if (!initialized)
	{
		termcap_init();
		tputs(tgetstr("ks", NULL), 1, &putint);
		ti.clear = tgetstr("cl", NULL);
		ti.k_up = tgetstr("ku", NULL);
		ti.k_down = tgetstr("kd", NULL);
		ti.k_left = tgetstr("kl", NULL);
		ti.k_right = tgetstr("kr", NULL);
		ti.k_backspace = tgetstr("kb", NULL);
		ti.move_left = tgetstr("le", NULL);
		ti.move_right = tgetstr("nd", NULL);
		ti.move_up = tgetstr("up", NULL);
		ti.move_down = tgetstr("do", NULL); 
		ti.move_c_h = tgetstr("ch", NULL);
		ti.save_c = tgetstr("sc", NULL);
		ti.restore_c = tgetstr("rc", NULL);
		ti.return_c = tgetstr("cr", NULL);
		ti.delete_char = tgetstr("dc", NULL);
		initialized = true;
	}
	return (&ti);
}

/*
**==================================================================
** DESCRIPTION:
**	Initialize readline(rl) INPUT OUTPUT stream preferences.	
*/
void	termios_init(void)
{
	int						success;
	static bool				initialized;
	static struct termios	rl_termios;

	if (!initialized)
	{
		termcap();
		success = tcgetattr(STDIN_FILENO, &rl_termios);
		if (success < 0)
			exit_message("Could not get interface attributes", \
			SYS_ERROR);
		rl_termios.c_lflag &= ~(ICANON | ECHO);
		initialized = true;
	}
	success = tcsetattr(STDIN_FILENO, TCSANOW, &rl_termios);
	if (success < 0)
		exit_message("Could not set interface attributes", \
		SYS_ERROR);
}

/*
**==================================================================
** DESCRIPTION:
**	Restore to system's INPUT OUTPUT stram preferences.
*/
void	termios_restore(void)
{
	int						success;
	static bool				initialized;
	static struct termios	sys_termios;

	if (!initialized)
	{
		success = tcgetattr(STDIN_FILENO, &sys_termios);
		if (success < 0)
			exit_message("Could not get interface attributes", \
			SYS_ERROR);
		initialized = true;
	}
	success = tcsetattr(STDIN_FILENO, TCSANOW, &sys_termios);
	if (success < 0)
		exit_message("Could not set interface attributes", \
		SYS_ERROR);
}
