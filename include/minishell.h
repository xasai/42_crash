#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include "readline.h"

/* struct defenitions */
# include "s_terminfo.h"
# include "s_shell.h"

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

extern t_shell *g_shell;

/*
**			MAIN.c
*/
void			handle_args(int ac, char **av);

/*
** 			INIT.c
*/
void			init_term(char **envp);
void			term_capability_db_init(void);
void			term_capability_data_init(void);
void			termios_init(void);

/*
**			EXIT.c
*/
void			exit_message(char *message, uint8_t code);
void			print_errno(char *message);


/*
**			INTERACT.c
*/
int				interact(void);

/*
**		 	READLINE/READLINE.c
*/
char			*readline(const char *prompt);
bool			ctl_char(char *line);

#endif
