#include "minishell.h"

void	quot_flagchange(char *ch, bool *flag)
{
	*ch *= -1;
	*flag ^= true;
}

size_t	get_argbuflen_withquot(char *line, size_t *arg_len)
{
	size_t	envvalue_len;
	size_t	envkey_len;
	size_t	tmp;
	bool	*qout_flag;

	qout_flag = (bool [2]){0};
	envvalue_len = 0;
	envkey_len = 0;
	while ((line[*arg_len] && (qout_flag[0] || qout_flag[1]))
		   || !ft_strchr("<>| \t", line[*arg_len]))
	{
		if (line[*arg_len] == '\"' && !qout_flag[0])
			quot_flagchange(&line[*arg_len], &qout_flag[1]);
		else if (line[*arg_len] == '\'' && !qout_flag[1])
			quot_flagchange(&line[*arg_len], &qout_flag[0]);
		else if (line[*arg_len] == '$' && !qout_flag[0])
		{
			line[*arg_len] = DOLLAR_CH;
			tmp = get_envkey_len(&line[*arg_len]);
			envkey_len += tmp;
			envvalue_len += get_envvalue_len(&line[*arg_len], tmp);
			*arg_len += tmp - 1;
		}
		++*arg_len;
	}
	return ((*arg_len + envvalue_len) - envkey_len);
}

size_t	get_strbufflen(char *str, size_t *str_len)
{
	size_t	tmp;
	size_t	envkey_len;
	size_t	envvalue_len;

	envkey_len = 0;
	envvalue_len = 0;
	while (str[*str_len])
	{
		if (str[*str_len] == '$')
		{
			str[*str_len] = DOLLAR_CH;
			tmp = get_envkey_len(&str[*str_len]);
			envkey_len += tmp;
			envvalue_len += get_envvalue_len(&str[*str_len], tmp);
			*str_len += tmp - 1;
		}
		++*str_len;
	}
	return ((*str_len + envvalue_len) - envkey_len);
}
