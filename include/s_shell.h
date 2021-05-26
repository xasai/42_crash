#ifndef S_SHELL_H
# define S_SHELL_H

/*
** На эту структуру будет ссылаться глобальный указатель *g_term
** Память под эту переменную выделяется на куче функцией init_first()
*/
typedef struct s_shell
{
	char				**envp;
	struct termios		old_termios;
	struct s_terminfo	terminfo;
}						t_shell;

/*
** S_SHELL_H
*/
#endif
