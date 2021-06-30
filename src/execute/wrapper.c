#include "minishell.h"

#define GETCWD_BUFF_SIZE 32

#define SHOW_DEBUG 0

//TODO check on error ret_pid or not?
void	_wait(pid_t pid)
{
	int	status;
	int	ret_pid;

	DEBUG("Waiting... for pid %d \n", pid);
	ret_pid = waitpid(pid, &status, 0);
	DEBUG("Wait inturupted by pid %d status 0x%04x\n", ret_pid, status);
	if (ret_pid != -1)
		g_sh->exit_status = WEXITSTATUS(status);
	DEBUG("exit_status: %d\n", g_sh->exit_status);
}

/*
**=================================================
** DESCRIPTION:
**	_getcwd is wrapper of function getcwd which will allocate enough
**	space for getcwd(3) buffer and will return its result.
*/
char	*_getcwd(void)
{
	char	*buf;
	size_t	size;

	size = GETCWD_BUFF_SIZE;
	buf = malloc(sizeof(*buf) * size);
	if (!buf)
		return (NULL);
	buf = getcwd(buf, size);
	while (buf == NULL && errno == ERANGE)
	{
		size += GETCWD_BUFF_SIZE;
		buf = getcwd(buf, size);
	}
	return (buf);
}
