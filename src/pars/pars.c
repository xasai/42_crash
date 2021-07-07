#include "minishell.h"

#define SHOW_DEBUG 0

void	copy_arg(char *line, size_t arg_len, char *buffer)
{
	size_t	envkey_len;
	size_t	envvalue_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < arg_len)
	{
		if (line[j] == DOLLAR_CH)
		{
			envkey_len = get_envkey_len(&line[j]);
			envvalue_len = get_envvalue_len(&line[j], envkey_len);
			expand_env(&buffer[i], &line[j]);
			i += envvalue_len;
			j += envkey_len - 1;
		}
		else if (!ft_strchr((char [4]){DOLLAR_CH, QUOT_CH, DQUOT_CH, '\0'},
			line[j]))
			buffer[i++] = line[j];
		++j;
	}
}

static char	*get_argbuf(char *line, size_t *arg_len)
{
	char	*buffer;
	size_t	qout_count;
	size_t	argbuflen_withqout;

	argbuflen_withqout = get_argbuflen_withquot(line, arg_len);
	qout_count = get_qoutcount(line, *arg_len);
	if (argbuflen_withqout == 0 && qout_count == 0)
		return (NULL);
	DEBUG("argbuff_len = %lu\n", argbuflen_withqout);
	buffer = ft_calloc(argbuflen_withqout - qout_count + 1, sizeof(char));
	if (buffer == NULL)
		exit_message("Memory allocation failure", SYS_ERROR);
	return (buffer);
}

char	*get_shellarg(char *line, size_t *arg_len)
{
	char	*buffer;

	buffer = get_argbuf(line, arg_len);
	copy_arg(line, *arg_len, buffer);
	return (buffer);
}

static void	line_pars(t_cmdlst *cmdl, char *line)
{
	size_t	arg_len;
	size_t	sep_len;
	char	*arg;

	while (*line)
	{
		arg_len = 0;
		skip_spasech(&line);
		arg = get_shellarg(line, &arg_len);
		line += arg_len;
		skip_spasech(&line);
		sep_len = get_sepch(line, cmdl);
		if (arg != NULL)
			cmdl->args = lineptrjoin(cmdl->args, arg);
		if (cmdl->sepch)
			cmdl = new_cmdlst(cmdl);
		line += sep_len;
	}
}

t_cmdlst	*ft_line_analyz(char *line)
{
	t_cmdlst	*cmdlst;

	if (ft_isempty_str(line))
		return (NULL);
	if (isunclosedquotes(line))
	{
		putstr_fd("Error: unclosed quotes\n", STDERR_FILENO);
		return (NULL);
	}
	cmdlst = new_cmdlst(NULL);
	line_pars(cmdlst, line);
	return (cmdlst);
}
