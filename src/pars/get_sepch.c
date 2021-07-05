#include "minishell.h"

#define SHOW_DEBUG 0

char *get_stopname(char *line, size_t *arg_len)
{
    size_t  j;
    size_t  i;
    char    *buffer;
    bool    *qout_flag;

    i = 0;
    j = 0;
    qout_flag = (bool [2]){0};
    while ((line[*arg_len] && (qout_flag[0] || qout_flag[1]))
           || !ft_strchr("<>| \t", line[*arg_len]))
    {
        if (line[*arg_len] == '\"' && !qout_flag[0])
            quot_flagchange(&line[*arg_len], &qout_flag[1]);
        else if (line[*arg_len] == '\'' && !qout_flag[1])
            quot_flagchange(&line[*arg_len], &qout_flag[0]);
        ++*arg_len;
    }
    buffer = xalloc(*arg_len - get_qoutcount(line,*arg_len) + 1, sizeof(char));
    while (j < *arg_len)
    {
        if(!ft_strchr((char [2]) {QUOT_CH, DQUOT_CH}, line[j]))
            buffer[i++] = line[j];
        ++j;
    }
    return (buffer);
}

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
	len += get_spasecount(&line[len]);
    line += len;
	rlst = append_rlst(&cmdl->rlst, type);
	if (type == '-')
        rlst->filename = get_hdoc(get_stopname(line, &filename_len));
	else
	    rlst->filename = get_shellarg(line, &filename_len);//TODO check this value
	DEBUG("line: \"%s\" filename \"%s\"\n", line, rlst->filename);
	len += get_spasecount(&line[filename_len]);
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
	else
	    while(line[len] == '>' || line[len] == '<')
		    len += _get_redirection(&line[len], cmdl);
	return (len);
}
