#ifndef MINISHELL_H
# define MINISHELL_H

/* struct defenitions */
# include "s_terminfo.h"
# include "s_shell.h"
/*--------------------*/

# include <unistd.h>
# include <fcntl.h>
# include <termcap.h> 
# include <term.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include <stdint.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>

# include "libft.h"
# include "readline.h"

# ifndef SYS_ERROR
#  define SYS_ERROR 2
# endif 


/*
**			MAIN.c
*/
void			handle_args(int ac, char **av);

/*
** 			INIT.c
*/
void			init_term(char **envp);

/*
**			EXIT.c
*/
void			exit_message(char *message, uint8_t code);
void			print_errno(void);


/*
**			INTERACT.c
*/
int				interact(void);

#endif /* MINISHELL_H */
