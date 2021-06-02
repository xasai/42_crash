#include "minishell.h"

unsigned int	strlen_ignore(char const *s, char c)
{
	int count;

	count = 0;
	while(*s)
		if (*s++ != c)
			++count;
	return (count);
}

char			*substr_ignore(char const *s, unsigned int start, size_t len, char c)
{
	int		i;
	char	*new;

	if (!s)
		return (NULL);
	i = 0;
	if (strlen_ignore(s, c) < start)
		return (ft_strdup(""));
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	while (s[start] && len--)
	{
		if (s[start] != c)
			new[i++] = s[start];
		++start;
	}
	new[i] = '\0';
	return (new);
}