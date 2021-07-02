#include "minishell.h"

unsigned int	strlen_ignore(char const *s, const char *sep)
{
	unsigned int count;

	count = 0;
	while(*s)
		if (!ft_strchr(sep, *s++))
			++count;
	return (count);
}

char	*substr_ignore(char const *s, unsigned int start_idx, size_t len, const char *sep)
{
    size_t      i;
	size_t      sub_len;
	char        *new;

	i = 0;
	//if (strlen_ignore(s, sep) < start_idx)
	//	return (ft_strdup(""));
	sub_len = strlen_ignore(s, sep);
	if(len > sub_len)
	    len = sub_len;
	//выделяется лишняя память если len + start_idx вываливается за пределы s
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	while (s[start_idx] && len--)
	{
		if (!ft_strchr(sep, s[start_idx]))
			new[i++] = s[start_idx];
		++start_idx;
	}
	new[i] = '\0';
	return (new);
}
