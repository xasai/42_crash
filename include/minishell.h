#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct/s_shell.h"
# include "struct/s_lsthead.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <unistd.h>
# include <fcntl.h>
# include <termcap.h> 

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>

# include <stdbool.h>
# include <stdint.h>
# include <sys/types.h>

# include <errno.h>

# include "pars.h"
# include "exec.h"
# include "libft.h"
# include "builtin.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define SYS_ERROR 2

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

# define PROMPT "crash$: "


/* 			INIT.c				*/
t_shell			*init_term(char **envp);

/*			INTERACT.c			*/
int				interact(t_shell *crash);

/*			CRASH_READLINE.c	*/
char			*crash_readline(t_shell *crash);

# ifdef __APPLE__
void			rl_replace_line (const char *text, int clear_undo);
# endif /* __APPLE__ */

/*			ENV.c				*/
char			*crash_getenv_ptr(char *name, char **envp);
char			*crash_getenv(char *name, char  **envp);
int				getenv_idx(char *name, char **envp);

/*			EXIT.c				*/
void			exit_message(char *message, uint8_t code);
void			print_errno(char *message);

#endif /* MINISHELL_H */
