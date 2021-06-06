#include "minishell.h"


unsigned int	strlen_ignore(char const *s, const char *sep)
{
	int count;

	count = 0;
	while(*s)
		if (!ft_strchr(sep, *s++))
			++count;
	return (count);
}

char			*substr_ignore(char const *s, unsigned int start, size_t len, const char *sep)
{
	int		i;
	char	*new;

	if (!s)
		return (NULL);
	i = 0;
	if (strlen_ignore(s, sep) < start)
		return (ft_strdup(""));
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	while (s[start] && len--)
	{
		if (!ft_strchr(sep, s[start]))
			new[i++] = s[start];
		++start;
	}
	new[i] = '\0';
	return (new);
}

