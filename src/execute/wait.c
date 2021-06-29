#include "minishell.h"

uint8_t	_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	printf("----------------------- 0x%x, %d\n",\
							status,(status & 0xff)); 
	return (WEXITSTATUS(status));
}
