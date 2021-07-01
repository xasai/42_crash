#include "minishell.h"


static int _output_dup(char *filename, bool append)
{
	int		flags;
	int		out_fd;	
	const mode_t perm = 0644;
	
	if (append)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	out_fd = open(filename, flags, perm);
	if (!out_fd)
		return (1);
	return (dup2(out_fd, STDOUT_FILENO) < 0);
}

static	int _input_dup(char *filename)
{
	int			input_fd;

	input_fd = open(filename, O_RDONLY);
	if (!input_fd)
		return (1);
	return (dup2(input_fd, STDIN_FILENO) < 0);
}

//TODO HEREDOC
void	redirect_ctl(t_cmdlst *cmd)
{
	int			err;
	char		type;
	t_redir_lst *redir_lst;
	
	redir_lst = cmd->rlst;
	while (redir_lst)
	{
		type = redir_lst->type;
		if (type == '-')
			err = _input_dup(NULL);
		else if (type == '>')
			err = _output_dup(NULL, false);
		else if (type == '+')
			err = _output_dup(NULL, true);
		if (err)
			print_errno("crash: ");
		redir_lst = redir_lst->next;
	}
	(void)cmd;
}
