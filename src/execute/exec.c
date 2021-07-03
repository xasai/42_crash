#include "minishell.h"

#define SHOW_DEBUG 0

inline static void	_set_sighandlers(void (*sighandler)(int))
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}


static void	_execve_fork(t_cmdlst *cmdl)
{
	pid_t	pid;

	if (builtin_exec(cmdl))
		return ;
	cmdl->pathname = get_path(cmdl->args[0]);
	if (NULL == cmdl->pathname)
		return ;
	pid = fork();
	if (pid < 0)
		print_errno("crash: fork()");
	else if (pid == 0)
	{	
		if (redirect_ctl(cmdl) == RETURN_FAILURE)
			exit(BUILTIN_FAILURE);
		else if (execve(cmdl->pathname, cmdl->args, g_sh->envp))
			exit_message(cmdl->pathname, SYS_ERROR);
	}
	_wait(pid);
	dup2(g_sh->saved_stdin, STDIN_FILENO);
	dup2(g_sh->saved_stdout, STDOUT_FILENO);
}

static void	_execve_nofork(t_cmdlst *cmdl)
{
	if (redirect_ctl(cmdl) || builtin_exec(cmdl))
		exit(g_sh->exit_status);
	cmdl->pathname = get_path(cmdl->args[0]);
	if (NULL == cmdl->pathname)
		exit(g_sh->exit_status);
	if (execve(cmdl->pathname, cmdl->args, g_sh->envp))
	{
		print_errno(cmdl->pathname);
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
	void		(*_execve)(t_cmdlst *);

	_set_sighandlers(_sig_wait);
	if (cmdl->sepch == '|')
	{
		cmdl = pipe_ctl(cmdl);
		_execve = _execve_nofork;
	}
	else
		_execve = _execve_fork;
	if (cmdl)
		_execve(cmdl);
	_set_sighandlers(SIG_DFL);
	if (g_sh->exit_status == SIGQUIT + 0x80)
		putstr_fd("^Quit\n", STDOUT_FILENO);
	else if (g_sh->exit_status == SIGINT + 0x80)
		putstr_fd("^C\n", STDOUT_FILENO);
}
