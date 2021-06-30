#include "minishell.h"


static int _new_out(char *filename, bool append)
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
		print_errno("crash: ");
	return (dup2(out_fd, STDOUT_FILENO));//TODO Check on -1
}
void	_void()
{
	_new_out(NULL, 0);
}
