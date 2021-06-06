#ifndef S_SHELL_H
# define S_SHELL_H

# include "s_history.h" 
/*
** На эту структуру будет ссылаться глобальный указатель *g_term
** Память под эту переменную выделяется на куче функцией init_first()
*/
typedef struct s_shell
{
	char				**envp;
	t_hist				*hist;
}						t_shell;

#endif /* S_SHELL_H */
