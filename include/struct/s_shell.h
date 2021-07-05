#ifndef S_SHELL_H
# define S_SHELL_H

# include <stdint.h>
# include <stdbool.h>

typedef struct s_shell
{
	char	*prompt;
	char	**envp;
	char	**path;
	int		saved_stdin;
	int		saved_stdout;
	uint8_t	exit_status;
	bool	is_signaled;
}			t_shell;

#endif /* S_SHELL_H */
