#include "minishell.h"

#define SHOW_DEBUG 0

inline static void	_set_sighandlers(void (*sighandler)(int))
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}


static void	_execve_fork(char *path, char **args, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		print_errno("crash: fork()");
	else if (pid == 0 && execve(path, args, envp))
		exit_message(path, SYS_ERROR);
	_wait(pid);
}

static void	_execve_nofork(char *path, char **args, char **envp)
{
	if (execve(path, args, envp))
	{
		print_errno(path);
		exit(EXIT_FAILURE);
	}
}

void	_sig_wait(int signum)
{
	_set_sighandlers(_sig_wait);
	_wait(0);
	g_sh->exit_status = 0x80 + signum;
}


void	cmdline_exec(t_cmdlst *cmdl)
{
	void		(*_execve)(char*, char **, char**);

	_set_sighandlers(_sig_wait);
	if (cmdl->sepch == '|')
	{
		cmdl = pipe_ctl(cmdl);
		_execve = _execve_nofork;
	}
	else
		_execve = _execve_fork;
	if (cmdl && !builtin_exec(cmdl))
	{
		redirect_ctl(cmdl);
		cmdl->name = get_path(cmdl->name);
		if (NULL == cmdl->name)
			return ;
		_execve(cmdl->name, cmdl->arg, g_sh->envp);
	}
	_set_sighandlers(SIG_DFL);
	if (g_sh->exit_status == SIGQUIT + 0x80)
		putstr_fd("Quit\n", STDOUT_FILENO);
	else if (g_sh->exit_status == SIGINT + 0x80)
		ft_putchar('\n');
}
