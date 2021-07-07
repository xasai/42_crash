#include "minishell.h"

#define SHOW_DEBUG 0

/*
**=================================================
** DESCRIPTION:
**	_wait is wrapper of function waitpid which will wait pid argument.
**	It will store exit_status if return of waitpid is not -1.	
*/
void	_wait(pid_t pid)
{
	int	status;
	int	ret_pid;

	DEBUG("Waiting... for pid %d \n", pid);
	ret_pid = waitpid(pid, &status, 0);
	DEBUG("Wait inturupted by pid %d status 0x%04x\n", ret_pid, status);
	DEBUG("Compare with pid %d \n", g_sh->exit_status_pid);
	if (ret_pid == g_sh->exit_status_pid)
	{
		g_sh->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_sh->exit_status = WTERMSIG(status) + 0x80;
		DEBUG("exit_status: %d\n", g_sh->exit_status);
	}
}
