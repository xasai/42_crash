#include "exec.h"

static void	execve_wrap(char *path, char **args, char **envp)
{
	execve(path, args, envp);
}

void	cmdline_exec(t_dlist *cmdlst, t_shell *crash)
{
	execve_wrap(cmdlst->name, cmdlst->arg, crash->envp);
}
