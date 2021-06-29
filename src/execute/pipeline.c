#include "minishell.h"

#define SHOW_DEBUG 1

//TODO case "echo cat|"
static int **get_pipes(t_cmdlst *cmdl)
{
	size_t	idx;
	size_t	count;
	int		**pipes;

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
		pipes[idx] = malloc(sizeof(**pipes) * 2);
		if (NULL == pipes[idx])
			exit_message("Memory allocation failure", SYS_ERROR);
		if (pipe(pipes[idx]))
			exit_message("Pipe allocation failure", SYS_ERROR);
		DEBUG("Created Pipe [%lu] %d, %d\n", idx, pipes[idx][0], pipes[idx][1]);
		idx++;	
	}
	return (pipes);
}

bool fork_n_dup(int read_end, int write_end, int fd_to_close)
{
	int		tmp;
	pid_t	fpid;

	fpid = fork();
	if (fpid == 0)
	{
		if (write_end != -1)
			tmp = dup2(write_end, STDOUT_FILENO);
		DEBUG("[PID %d] dup2(%d,%d)\n",getpid(), write_end,tmp);
		if (read_end != -1)
			tmp = dup2(read_end, STDIN_FILENO);
		DEBUG("[PID %d] dup2(%d,%d)\n",getpid(), read_end,tmp);
		close(fd_to_close);
	}
	else if (fpid == -1)
	{// KILL all childs or no?
		print_errno("crash: fork()");
		return (0);
	}
	return (fpid == 0);
}

//Main
t_cmdlst	*pipe_ctl(t_cmdlst *cmdl)
{
	int			**pipes;
	size_t		cmd_idx;
	uint8_t		err;

	cmd_idx = 0;
	pipes = get_pipes(cmdl);
	while (cmdl)
	{
		if (NULL == cmdl->prev)
		{// Первая команда меняет только stdout
			if (fork_n_dup(-1, pipes[cmd_idx][1], pipes[0][0]))
				return (cmdl);
		}
		else if (NULL == cmdl->next)
		{// Последняя меняет только stdin
			if (fork_n_dup(pipes[cmd_idx - 1][0], -1, pipes[cmd_idx - 1][1]))
				return (cmdl);
		}// Все остальные меняют и stdin и stdout
		else if (fork_n_dup(pipes[cmd_idx - 1][0], pipes[cmd_idx][1], -1))
			return (cmdl);
		cmd_idx++;
		cmdl = cmdl->next;
	}
	while (cmd_idx--)
	{
		err = _wait(0);
		if (err)
			g_sh->status_code = err;
	}
	printf("=================== %d\n",g_sh->status_code);
	return (NULL);
}
