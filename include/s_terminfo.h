#ifndef S_TERMINFO_H
# define S_TERMINFO_H

# include <termios.h>

/*
** На эту структуру будет ссылаться глобальный указатель *g_term 
** Память под эту переменную выделяется на куче функцией init_first()
*/

typedef struct s_terminfo
{
	char			**envp;
	struct termios	termios;
}					t_terminfo;

#endif
