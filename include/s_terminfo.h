#ifndef S_TERMINFO_H
# define S_TERMINFO_H

# include <termios.h>

struct s_terminfo
{
	char	*k_up;
	char	*k_down;
	char	*k_left;
	char	*k_right;
	char	*k_backspace;
	char	*move_left;
	char	*move_right;
	char	*clear;
	char	*save_c;
	char	*restore_c;
};

#endif /* S_TERMINFO_H */
