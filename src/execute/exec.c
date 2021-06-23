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

void	redirect_output(t_cmdlst *cmdl);

void	cmdline_exec(t_cmdlst *cmdl)
{
	_set_sighandlers();
	if (ft_strchr(">+", cmdl->sepch))
		redirect_output(cmdl);
	if (builtin_exec(cmdl))
		;
	else 
	{
		cmdl->name = get_path(cmdl->name);
		execve_wrap(cmdl->name, cmdl->arg, g_sh->envp);
	}
	_set_sigdefault();
}
