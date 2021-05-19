#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <fcntl.h>
#include <termcap.h> 


/*
**			MAIN.c
*/
void	handle_args(int ac, char **av);


/*
** 			INIT.c
*/
void	init_first(int ac, char **av);

#endif
