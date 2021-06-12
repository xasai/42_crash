#ifndef MINISHELL_H
# define MINISHELL_H

/* struct defenitions */
# include "s_shell.h"
# include "s_lsthead.h"
/*--------------------*/
# include <readline/readline.h>
# include <readline/history.h>

# include <unistd.h>
# include <fcntl.h>
# include <termcap.h> 

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>

/*-----data types-----*/
# include <stdbool.h>
# include <stdint.h>
# include <sys/types.h>
/*--------------------*/

# include <errno.h>
//# include <limits.h>

# include "pars.h"
# include "exec.h"
# include "libft.h"
# include "wrapper.h"

# ifndef SYS_ERROR
#  define SYS_ERROR 2
# endif 

# define PROMPT "crash$: "

/* 			INIT.c				*/
t_shell			*init_term(char **envp);

/*			INTERACT.c			*/
int				interact(t_shell *crash);

/*			CRASH_READLINE.c	*/
char			*crash_readline(t_shell *crash);

/*			EXIT.c				*/
void			exit_message(char *message, uint8_t code);
void			print_errno(char *message);

#endif /* MINISHELL_H */
