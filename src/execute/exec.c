#include "exec.h"

#define SHOW_DEBUG 1

void _sig_skip(int signum)
{
	return ;
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

	_set_sighandlers(_sig_skip);
	if (cmdl->sepch == '|')
	{
		pipe_cmd = pipe_ctl(cmdl);
		//redir_ctl
		if (pipe_cmd && !builtin_exec(cmdl))
		{
			pipe_cmd->name = get_path(pipe_cmd->name);
			DEBUG("executing pipe %s ...\n", pipe_cmd->name);;
			execve_nofork(pipe_cmd->name, pipe_cmd->arg, g_sh->envp);
		}
	}
	else
	{
		//redir_ctl
		if (!builtin_exec(cmdl))
		{
			cmdl->name = get_path(cmdl->name);
			execve_fork(cmdl->name, cmdl->arg, g_sh->envp);
		}
	}
	_set_sighandlers(SIG_DFL);
}
