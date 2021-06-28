#include "minishell.h"

#define SHOW_DEBUG 1

static void *_fork_error(pid_t pid)
{
	print_errno("crash: fork()");
	kill(pid, SIGKILL);
	return (NULL);
}

pid_t	fork_n_dup(int read_end, int write_end)
{
	pid_t	pid_out;
	pid_t	pid_in;

	pid_out = fork();	
	if (!pid_out)
	{
		close(read_end);			
		int tmp = dup2(write_end, 1);
		DEBUG("OUTPUT dup2(%d,%d)\n",write_end,tmp);
		return (1);
	}
	pid_in = fork();
	if (!pid_in)
	{
		close(write_end);			
		int tmp = dup2(read_end, 0);
		DEBUG("INPUT dup2(%d,%d)\n",read_end,tmp);
		return (2);
	}
	if (pid_out == -1)
		return (-pid_in);
	return (0);
}

//Код который будет обрабатывать пайпы:
// 1 - Будет запускать ВСЕ в дочерних процессах
// 2 - Будет связывать stdout и stdin между всеми пайпами
// 3 - Для каждой команды самостоятельно предпримет их редиректы в их вилках
// 4 - вернет status_code последней отработаной команды.
t_cmdlst	*pipe_ctl(t_cmdlst *cmdl)
{
	int			pipefd[2];
	int			wstatus;
	int			fork_id;
	t_cmdlst	*cur_command;
	t_cmdlst	*next_command;

	cur_command = cmdl;
	while (cur_command && cur_command->sepch == '|')
	{	
		if (pipe(pipefd) == -1)
			print_errno("crash: pipe()");	
		next_command = cur_command->next;
		fork_id = fork_n_dup(pipefd[0], pipefd[1]);
		if (fork_id < 0)
			return (_fork_error(fork_id));
		else if (fork_id == 1)
			return (cur_command);
		else if (fork_id == 2)
			return (next_command);
		cur_command = next_command;
	}
	waitpid(0, &wstatus, WUNTRACED);
	WIFEXITED(wstatus);
	return NULL;
}
