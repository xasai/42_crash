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

//TODO check how it works in bash with pipes
//TODO check redirection followed empty cmdlst
//TODO check how multy directions works "some command > file < some command"
int redirect_ctl(t_cmdlst *cmdl)
{
	//This func should be already in fork if not builtin
	//Also if in fork we can not to dup our streams back
	int		new_fd;	
	char	*out_name;

	new_fd = -1;
	while (cmdl->sepch)
	{
		close(new_fd);
		if (cmdl->sepch == '>' || cmdl->sepch == '+')	
		{	
			out_name = cmdl->next->name;
			new_fd = _new_out(out_name, cmdl->sepch == '+');
		}
		cmdl = cmdl->next;
	}
	return (new_fd);
}
