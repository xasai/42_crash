#ifndef S_TERMINFO_H
# define S_TERMINFO_H

# include <termios.h>

struct s_terminfo
{
	char	*clear;
	char	*k_up;
	char	*k_down;
	char	*k_left;
	char	*k_right;
	char	*k_backspace;
	char	*move_left;
	char	*move_right;
	char	*move_up;
	char	*move_down;
	char	*move_c_h;
	char	*delete_char;
	char	*save_c;
	char	*restore_c;
	char	*return_c;
};

#endif /* S_TERMINFO_H */
