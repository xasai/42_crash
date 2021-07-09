#include "minishell.h"

#define SHOW_DEBUG 0

typedef int (*t_pipes)[2];

/*
**=================================================
** DESCRIPTION:
**	close_all_pipes() close all pipes and frees t_pipes	
*/
static void	close_all_pipes(t_pipes pipes, t_cmdlst *cmdl)
{
	size_t	idx;
	
	if (!cmdl)
		return ;
	while (cmdl->prev)
		cmdl = cmdl->prev;
	idx = 0;
	while (cmdl && cmdl->sepch == '|')
	{
		close(pipes[idx][0]);
		close(pipes[idx][1]);
		cmdl = cmdl->next;
		idx++;
	}
	free(pipes);
}

inline static void	*_ret_(t_pipes pipes, void *cmdl)
{
	close_all_pipes(pipes, cmdl);
	return (cmdl);
}

/*
**=================================================
** DESCRIPTION:
**	get_pipes() allocates t_pipes with count of pipe in cmdl.
**	Call pipe() for every t_pipes element.
**	
** RETURN:
**	t_pipes array 
*/
static t_pipes	get_pipes(t_cmdlst *cmdl)
{
	size_t	idx;
	size_t	count;
	t_pipes	pipes;

	count = 0;
	while (cmdl->sepch == '|')
	{
		count++;
		cmdl = cmdl->next;
	}
	pipes = ft_calloc(sizeof(*pipes), count);
	if (NULL == pipes)
		exit_message("Memory allocation failure", SYS_ERROR);
	idx = 0;
	while (idx < count)
	{
		if (pipe(pipes[idx]))
			print_errno("Pipe allocation failure");
		idx++;
	}
	return (pipes);
}

/*
**=================================================
** DESCRIPTION:
**	fork_n_dup() creates fork and dup his STDOUT_FILENO with write_end,
**	and his STDIN_FILENO with read_end.
**	
** RETURN:
**		PID of child in parent proccess.
**		0 in child proccess.
*/
static pid_t	fork_n_dup(int read_end, int write_end)
{
	pid_t	fpid;

	fpid = fork();
	if (fpid == 0)
	{
		if (write_end != -1)
			dup2(write_end, STDOUT_FILENO);
		if (read_end != -1)
			dup2(read_end, STDIN_FILENO);
	}
	else if (fpid == -1)
		print_errno("crash: fork()");
	return (fpid);
}

/*
**=================================================
** DESCRIPTION:
**	pipe_ctl() create pipe for every pipe in cmdlst.
**	Fork proccess and close all non-need pipe's ends.
**
** RETURN:
**	It returns t_cmdlst* command in child proccesses,
**	NULL in parent proccess.
*/
t_cmdlst	*pipe_ctl(t_cmdlst *cmdl)
{
	pid_t		fpid;
	t_pipes		pipes;
	size_t		cmd_idx;

	cmd_idx = 0;
	pipes = get_pipes(cmdl);
	while (cmdl && (cmdl->sepch == '|' || cmdl->prev->sepch == '|'))
	{
		if (NULL == cmdl->prev)			// first cmd command 
			fpid = fork_n_dup(-1, pipes[cmd_idx][1]);
		else if (NULL == cmdl->next)	// last cmd command 
			fpid = fork_n_dup(pipes[cmd_idx - 1][0], -1);
		else							// middle commands 
			fpid = fork_n_dup(pipes[cmd_idx - 1][0], pipes[cmd_idx][1]);
		if (fpid == 0)
			return (_ret_(pipes, cmdl));
		cmd_idx++;
		if (NULL == cmdl->next)
			close_all_pipes(pipes, cmdl);
		cmdl = cmdl->next;
	}
	g_sh->exit_status_pid = fpid;
	while (cmd_idx--)
		_wait(-1);
	return (NULL);
}
