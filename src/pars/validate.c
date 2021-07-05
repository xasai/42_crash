#include "minishell.h"

static bool	_error(char *message)
{
	putstr_fd("Invalid syntax ", STDERR_FILENO);
	if (message)
		putstr_fd(message, STDERR_FILENO);
	putchar_fd('\n', STDERR_FILENO);
	return (RETURN_FAILURE);

}

bool	_validate_rlst(t_redir_lst *rlst)
{
	while (rlst)
	{
		if (rlst->type && (!rlst->filename || !ft_strlen(rlst->filename)))		
			return (RETURN_FAILURE);
		rlst = rlst->next; 
	}
	return (RETURN_SUCCESS);
}

bool	validate_cmd(t_cmdlst *cmdl)
{

	while (cmdl)
	{
		if (cmdl->rlst && _validate_rlst(cmdl->rlst))
			return (_error("near redirection"));
		else if (!cmdl->args)
			return (_error("near 'newline'"));
		cmdl = cmdl->next;
	}
	return (RETURN_SUCCESS);
}
