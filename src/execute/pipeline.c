#include "minishell.h"

static void *_fork_error(pid_t pid)
{
	print_errno("crash: fork()");
	kill(pid, SIGKILL);
	return (NULL);
}

pid_t	fork_n_dup(int new_in, int new_out)
{
	pid_t	pid_out;
	pid_t	pid_in;

	pid_out = fork();	
	if (!pid_out)
	{
		close(new_in);			
		close(STDOUT_FILENO);
		dup2(STDOUT_FILENO, new_out);
		return (1);
	}
	pid_in = fork();
	if (!pid_in)
	{
		close(new_out);			
		close(STDIN_FILENO);
		dup2(STDIN_FILENO, new_in);
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
	wait(&wstatus);
	return NULL;
}
