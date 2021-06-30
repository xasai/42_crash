#include "exec.h"

#define SHOW_DEBUG 0

inline static void	_set_sighandlers(void (*sighandler)(int))
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}

void _sig_wait(int signum)
{
	g_sh->exit_status = 0x80 + signum;
	_set_sighandlers(SIG_DFL);
	if (signum == SIGQUIT)
		write(STDOUT_FILENO, "Quit\n", 5);
	else
		write(STDOUT_FILENO, "\n", 1);
	wait(0);
}

static void	execve_fork(char *path, char **args, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		print_errno("fork()");
	else if (pid == 0)
	{
		_set_sighandlers(SIG_DFL);
		if (execve(path, args, envp))
			exit_message(path, SYS_ERROR);
	}
	_wait(pid);
}

static void	execve_nofork(char *path, char **args, char **envp)
{
	if (execve(path, args, envp))
	{
		print_errno(path);
		exit(EXIT_FAILURE);
	}
}

void	cmdline_exec(t_cmdlst *cmdl)
{
	void		(*_execve)(char*, char **, char**);

	_set_sighandlers(_sig_wait);
	if (cmdl->sepch == '|')
	{
		cmdl = pipe_ctl(cmdl);
		_execve = execve_nofork;
	}
	else
		_execve = execve_fork;
	if (cmdl && !builtin_exec(cmdl))
	{
		//redirect_ctl
		cmdl->name = get_path(cmdl->name);
		if (NULL == cmdl->name)
			return ;
		_execve(cmdl->name, cmdl->arg, g_sh->envp);
	}
	_set_sighandlers(SIG_DFL);
}
