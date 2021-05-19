#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "s_terminfo.h"

# include <unistd.h>
# include <fcntl.h>
# include <termcap.h> 
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

# include <stdint.h>
# include <limits.h>

extern t_terminfo *g_term;

/*
**			MAIN.c
*/
void			handle_args(int ac, char **av);

/*
** 			INIT.c
*/
void			init_first(int ac, char **av, char **envp);
void			term_capability_data_init(void);
struct termios	termios_init(void);

/*
**			EXIT.c
*/
void			exit_message(char *message, uint8_t code);

/*
**		 	READLINE/READLINE.c
*/
int				interact(void);
char			*readline(const char *prompt);

#endif
