#ifndef CRASH_READLINE_H
# define CRASH_READLINE_H

# include "struct/s_shell.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>

# include "minishell.h"

# define PROMPT	"crash$: "

char	*crash_readline(t_shell *crash);

#endif /* CRASH_READLINE_H */
