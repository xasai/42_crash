#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h> //FIXME

# include "debug.h"
# include "struct/s_shell.h"
# include "struct/s_cmdlst.h"

# include "pars.h"
# include "exec.h"
# include "libft.h"
# include "builtin.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>

# include <stdbool.h>
# include <stdint.h>
# include <sys/types.h>
# include <errno.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define SYS_ERROR 2

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

# define PROMPT "crash$: "

# ifdef __APPLE__
void			rl_replace_line(const char *text, int clear_undo);
# endif /* __APPLE__ */

extern t_shell	*g_sh;

/* 				init.c				*/

void			init_sh(char **envp);

/*				interact.c			*/

int				interact(void);

/*				crash_readline.c	*/

char			*crash_readline(void);

/*				env.c				*/

int				getenv_idx(char *name);
char			*getenv_name(char *varstr);
char			*crash_getenv(char *name);
void			crash_setenv(char *name, char *value);
void			crash_unsetenv(char *name);
size_t			get_envkey_len(char *line);
size_t			get_envvalue_len(char *line, size_t envkey_len);
void			expand_env(char *buffer, char *line);

/*				free.c				*/

void			cmdlst_free(t_cmdlst *cmdl);
void			rlst_free(void); //TODO

/*				exit.c				*/

void			exit_message(char *message, uint8_t code);
void			print_errno(char *message);
void			xuinya(void);

#endif /* MINISHELL_H */
