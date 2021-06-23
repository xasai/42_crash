#include "minishell.h"

void	redirect_output(t_cmdlst *cmdl)
{
	const mode_t perm = 0644;
	int		flags;
	int		output_fd;	
	char	*filename;
	
	filename = cmdl->next->name;
	flags = O_CREAT | O_WRONLY;
	if (cmdl->sepch == '+')
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	output_fd = open(filename, flags, perm);
	if (!output_fd)
		print_errno("crash: ");
	write(output_fd, filename, ft_strlen(filename));
}
