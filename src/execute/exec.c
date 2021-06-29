#include "exec.h"

#define SHOW_DEBUG 1

void _sig_wait(int signum)
{
	wait(NULL);	
	write(STDOUT_FILENO, "\n", 1);
	(void)signum;
}

inline static void	_set_sighandlers(void (*sighandler)(int))
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}


static void	execve_fork(char *path, char **args, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		print_errno("fork()");
	else if (pid == 0 && execve(path, args, envp))
	{
		print_errno(path);
		exit(EXIT_FAILURE);
	}
	g_sh->status_code = _wait(pid);
}

static void	execve_nofork(char *path, char **args, char **envp)
{
	if (execve(path, args, envp))
	{
		print_errno(path);
		exit(EXIT_FAILURE);
	}
}

t_cmdlst	*pipe_ctl(t_cmdlst *cmdl);

void	cmdline_exec(t_cmdlst *cmdl)
{
	t_cmdlst	*pipe_cmd;

	_set_sighandlers(_sig_wait);
	if (cmdl->sepch == '|')
	{
		pipe_cmd = pipe_ctl(cmdl);
		//redirect_ctl
		DEBUG("executing %s\n", cmdl->name);
		if (pipe_cmd && !builtin_exec(cmdl))
		{
			pipe_cmd->name = get_path(pipe_cmd->name);
			execve_nofork(pipe_cmd->name, pipe_cmd->arg, g_sh->envp);
		}
	}
	else
	{
		//redirect_ctl
		if (!builtin_exec(cmdl))
		{
			cmdl->name = get_path(cmdl->name);
			execve_fork(cmdl->name, cmdl->arg, g_sh->envp);
		}
	}
	_set_sighandlers(SIG_DFL);
}
