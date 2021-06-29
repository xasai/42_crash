#include "minishell.h"

#define SHOW_DEBUG 0

void _wait(pid_t pid)
{
	int	status;
	int ret_pid;

	DEBUG("Waiting... for pid %d \n", pid);
	ret_pid = waitpid(pid, &status, 0);//TODO check on error
	DEBUG("Wait inturupted by pid %d status 0x%04x\n", ret_pid, status);
	if (ret_pid != -1)
		g_sh->exit_status = WEXITSTATUS(status);
	DEBUG("exit_status: %d\n", g_sh->exit_status);
}
