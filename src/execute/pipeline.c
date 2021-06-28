#include "minishell.h"

#define SHOW_DEBUG 1

//Need somehow to check and kill all processes
static void *_fork_error()
{
	print_errno("crash: fork()");
	return (NULL);
}

bool fork_n_dup(int read_end, int write_end, int close1, int close2)
{
	int		tmp;
	pid_t	fpid;

	DEBUG("read_end: %d write_end: %d close1: %d close2: %d\n",
			read_end, write_end, close1, close2);
	fpid = fork();
	if (fpid == 0)
	{
		if (write_end != -1)
		{
			tmp = dup2(write_end, STDOUT_FILENO);
			DEBUG("[PID %d] dup2(%d,%d)\n",getpid(), write_end,tmp);
		}
		if (read_end != -1)
		{
			tmp = dup2(read_end, STDIN_FILENO);
			DEBUG("[PID %d] dup2(%d,%d)\n",getpid(), read_end,tmp);
		}
		close(close1);
		close(close2);
		return (true);
	}
	else if (fpid == -1)
		_fork_error();
	DEBUG("Attached PID %d\n", fpid); 
	DEBUG("Close(%d, %d, %d, %d) in main proc \n",\
			read_end, write_end, close1, close2); 
	/*
	close(read_end); 
	close(write_end);
	close(close1);
	close(close2);
	*/
	return (false);
}

//Main
t_cmdlst	*pipe_ctl(t_cmdlst *cmdl)
{
	int			pipe_1[2];
	int			pipe_2[2];
	t_cmdlst	*cur_command;
	t_cmdlst	*next_command;
	
	cur_command = cmdl;
	next_command = cmdl->next;
	if (pipe(pipe_1) == -1)
	{
		print_errno("crash: pipe()");
		return (NULL);
	}
	//  Редиректим только stdout в write_end[1], а read_end[0] закрываем
	if (fork_n_dup(-1, pipe_1[1], pipe_1[0], -1))
		return (cur_command);
	while (next_command->sepch == '|')
	{
		cur_command = next_command;
		if (pipe(pipe_2) == -1)
		{
			print_errno("crash: pipe()");
			return (NULL);
		}
		// Редиректим пред. stdin read_end[0], a пред. write_end[1] закрываем
		// Редиректим stdout в write_end[1], а read_end[0] закрываем
		if (fork_n_dup(pipe_1[0], pipe_2[1], pipe_1[1], pipe_2[0]))
			return (cur_command);
		next_command = cur_command->next;

		// Новый пайп становится предъидущем
		pipe_1[0] = pipe_2[0];
		pipe_1[1] = pipe_2[1];
	}

	// Редиректим stdin read_end[0], a write_end[1] закрываем
	if (fork_n_dup(pipe_1[0], -1, pipe_1[1], -1))
		return (next_command);
	return NULL;
}
