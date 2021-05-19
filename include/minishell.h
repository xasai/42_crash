#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"

#include <unistd.h>
#include <fcntl.h>
#include <termcap.h> 
#include <stdlib.h>
#include <stdint.h>

/*
**			MAIN.c
*/
void	handle_args(int ac, char **av);


/*
** 			INIT.c
*/
void	init_first(int ac, char **av);
void	term_capability_data_init(void);

/*
**			EXIT.c
*/
void	exit_message(char *message, uint8_t code);

#endif
