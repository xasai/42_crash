#include "minishell.h"

static bool	_error_syntax(char *message)
{
	putstr_fd("Error syntax ", STDERR_FILENO);
	if (message)
		putstr_fd(message, STDERR_FILENO);
	putchar_fd('\n', STDERR_FILENO);
	return (RETURN_FAILURE);
}

inline static bool	_validate_rlst(t_redir_lst *rlst)
{
	while (rlst)
	{
		if (rlst->type && (!rlst->filename || !ft_strlen(rlst->filename)))
			return (RETURN_FAILURE);
		rlst = rlst->next;
	}
	return (RETURN_SUCCESS);
}

inline static bool	_validate_pipe(t_cmdlst *cmdl)
{
	if (cmdl->sepch && ((!cmdl->next->rlst && !cmdl->next->args)
			|| (!cmdl->args && !cmdl->rlst)))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

bool	validate_cmd(t_cmdlst *cmdl)
{
	if (!cmdl)
		return (RETURN_FAILURE);
	while (cmdl)
	{
		if (_validate_rlst(cmdl->rlst))
			return (_error_syntax("near redirection"));
		else if (_validate_pipe(cmdl))
			return (_error_syntax("near 'pipe'"));
		cmdl = cmdl->next;
	}
	return (RETURN_SUCCESS);
}
