#ifndef S_SHELL_H
# define S_SHELL_H

#include <stdint.h>

typedef struct s_shell
{
	char	*prompt;
	char	**envp;
	char	**path;
	int		saved_stdin;
	int		saved_stdout;
	uint8_t	exit_status;
}			t_shell;

#endif /* S_SHELL_H */
