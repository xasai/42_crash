#include "minishell.h"

#define SHOW_DEBUG 0

size_t	_get_redirection(char *line, t_cmdlst *cmdl)
{
	t_redir_lst		*rlst;
	char			type;
	size_t			len;
	size_t			filename_len;

	len = 0;
	filename_len = 0;
	type = line[len];
	if (line[len] == '<' && line[len+ 1] == '<')
		type = '-';
	else if (line[len] == '>' && line[len + 1] == '>')
		type = '+';
	len = 1;
	if (type == '+' || type == '-')
		len++;
	while(ft_isspace(line[len]))
	    ++len;
    line += len;
	rlst = append_rlst(&cmdl->rlst, type);
	rlst->filename = get_shellarg(line, &filename_len);//TODO check this value
	return (filename_len + len);
	
}

size_t	get_sepch(char *line, t_cmdlst *cmdl)
{
	size_t	len;

	len = 0;
	if (*line == '|')
	{
		cmdl->sepch = *line;
		return (1); 
	}
	else if (*line == '>' || *line == '<')
		len = _get_redirection(line, cmdl);
	DEBUG("Sepch is: \"%*s\"\n",(int)len, line);
	return (len);
}
