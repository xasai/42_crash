#include "minishell.h"

static	char *_get_hdoc_filename(void)
{
	static int		num = 0;
	const char		*part1= "/tmp/hdoc";
	char			*part2;
	char			*filename;
	
	num++;
	if (num < 0)
		num = 0;
	part2 = ft_itoa(num);
	filename = ft_strjoin(part1, part2);
	free(part2);
	if (NULL == filename)
		exit_message("Memory allocation failure", SYS_ERROR);
	return (filename);
}

void	read_hdoc(t_redir_lst *rlst, char *delim)
{
	int		hdoc_fd;

	rlst->filename = _get_hdoc_filename();
	hdoc_fd = open(rlst->filename, O_CREAT | O_WRONLY, 0600);
	if (-1 == hdoc_fd)
	{
		print_errno("crash: ");
		return ;
	}
	(void)delim;
}
