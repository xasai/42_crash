#include "exec.h"

static void	execve_wrap(char *path, char **args, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;				

	pid = fork();
	if (pid < 0)
		print_errno("fork()");
	else if (pid == 0 && execve(path, args, envp))
		print_errno(path);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		if (wpid < 0)
			putstr_fd("wpid = -1\n", STDERR_FILENO);
	}
}

void	cmdline_exec(t_dlist *cmdlst, t_shell *crash)
{
	cmdlst->name = get_path(cmdlst->name, crash->path);
	execve_wrap(cmdlst->name, cmdlst->arg, crash->envp);
}
