#include "exec.h"

void _sig_skip(int signum)
{
	return ;
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
		wpid = waitpid(pid, &status, WUNTRACED);
		if (wpid < 0)
			print_errno("crag_sh");	
	}
}

int	redirect_ctl(t_cmdlst *cmdl);

void	cmdline_exec(t_cmdlst *cmdl)
{
	int	redir_fd;

	redir_fd = -1;
	_set_sighandlers();
	// if pipe
	//	do pipe
	// else if sepch 
	//	do redirection
	if (cmdl->sepch && cmdl->sepch != '|')
		redir_fd = redirect_ctl(cmdl);
	if (builtin_exec(cmdl))
		;
	else 
	{
		cmdl->name = get_path(cmdl->name);
		execve_wrap(cmdl->name, cmdl->arg, g_sh->envp);
	}
	if (redir_fd > -1)
	{
		close(redir_fd);
		dup2(g_sh->saved_stdout, redir_fd/*or STDOUT_FILENO ?*/);
	}
	_set_sigdefault();
}
