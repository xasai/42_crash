#include "minishell.h"

inline static bool	_error(char *filename)
{
	print_errno("crash:");
	putendl_fd(filename, STDERR_FILENO);
	return (true);
}

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
	return (dup2(out_fd, STDOUT_FILENO) == -1);
}

static	int _input_dup(char *filename)
{
	int			input_fd;

	input_fd = open(filename, O_RDONLY);
	if (!input_fd)
		return (1);
	return (dup2(input_fd, STDIN_FILENO) == -1);
}

bool	redirect_ctl(t_cmdlst *cmd)
{
	int			err;
	char		type;
	char		*filename;
	t_redir_lst *redir_lst;
	
	redir_lst = cmd->rlst;
	while (redir_lst)
	{
		type = redir_lst->type;
		filename = redir_lst->filename;
		if (type == '-')
			err = _input_dup(filename);
		else if (type == '-')
			err = _input_dup(filename);
		else if (type == '>')
			err = _output_dup(filename, false);
		else if (type == '+')
			err = _output_dup(filename, true);
		if (err)
			return (_error(filename));
		redir_lst = redir_lst->next;
	}
	return (false);
}
