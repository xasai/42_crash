#include "exec.h"

int	_sig_skip(int signum)
{
	return (0);
	(void)signum;
}

inline static void	_set_sighandlers(void)
{
	signal(SIGINT, _sig_skip);
	signal(SIGQUIT, _sig_skip);
}

inline static void	_set_sigdefault(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	execve_wrap(char *path, char **args, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;				

	pid = fork();
	if (pid < 0)
		print_errno("fork()");
	else if (pid == 0 && execve(path, args, envp))
	{
		print_errno(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		wpid = wait(&status);
		if (wpid < 0)
			print_errno("crash");	
	}
}

void	cmdline_exec(t_dlist *cmdlst, t_shell *crash)
{
	_set_sighandlers();
	if (builtin_exec(cmdlst, crash))
		;
	else 
	{
		cmdlst->name = get_path(cmdlst->name, crash->path);
		execve_wrap(cmdlst->name, cmdlst->arg, crash->envp);
	}
	_set_sigdefault();
}
