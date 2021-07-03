#include "minishell.h"

#define SHOW_DEBUG 0

typedef int (*t_pipes)[2];


inline static void	_close(int fd)
{
	if (fd != -1)
		close(fd);
}

static t_pipes get_pipes(t_cmdlst *cmdl)
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
**	fork_n_dup().
**	Call dup2 read_end to STDIN, if read_end != -1
**	Call dup2 write_end to STDOUT, if write_end != -1
**	Close fd_to_close;.
**	Close all read_end and write_end in parent process.
**
** RETURN:
**		PID of forked process in parent.
**		0 in child
*/
pid_t	fork_n_dup(int read_end, int write_end, int fd_to_close)
{
	pid_t	fpid;

	fpid = fork();
	if (fpid == 0)
	{
		if (write_end != -1)
			dup2(write_end, STDOUT_FILENO); //TODO check dup2
		if (read_end != -1)
			dup2(read_end, STDIN_FILENO);
		_close(fd_to_close);
		return (fpid);
	}
	else if (fpid == -1)
	{
		print_errno("crash: fork()");
		return (-1);//TODO KILL all childs or no
	}
	_close(read_end);
	_close(write_end);
	return (fpid);
}

/*
**=================================================
** DESCRIPTION:
**	pipe_ctl() controlling pipes and forks in t_cmdlst.
**	It will fork count of t_cmdlst processess concatenated
**	with pipes. And then it will concatenate its stdout&stdin
**	fildes.
**
** RETURN:
**		It returns t_cmdlst* command in child processes,
**		and NULL in parent proccess.
*/
t_cmdlst	*pipe_ctl(t_cmdlst *cmdl)
{
	t_pipes		pipes;
	size_t		cmd_idx;

	cmd_idx = 0;
	pipes = get_pipes(cmdl);
	while (cmdl && (cmdl->sepch == '|' || cmdl->prev->sepch == '|'))
	{
		if (NULL == cmdl->prev)
		{// Первая команда меняет только stdout
			if (!fork_n_dup(-1, pipes[cmd_idx][1], pipes[0][0]))
				return (cmdl);
		}
		else if (NULL == cmdl->next)
		{// Последняя меняет только stdin
			if (!fork_n_dup(pipes[cmd_idx - 1][0], -1, pipes[cmd_idx - 1][1]))
				return (cmdl);
		}// Все остальные меняют и stdin и stdout
		else if (!fork_n_dup(pipes[cmd_idx - 1][0], pipes[cmd_idx][1], -1))
			return (cmdl);
		cmd_idx++;
		cmdl = cmdl->next;
	}
	while (cmd_idx--)
		_wait(0);
	free(pipes);
	return (NULL);
}
