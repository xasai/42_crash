#ifndef S_SHELL_H
# define S_SHELL_H

#include <stdint.h>

typedef struct s_shell
{
	char	*prompt;
	char	**envp;
	char	**path;
	uint8_t	status_code;
}			t_shell;

#endif /* S_SHELL_H */
