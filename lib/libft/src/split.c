#include "libft.h"

static char	**split_clr(char **p)
{
	int	i;

	i = -1;
	while (p[++i] != NULL)
		free(p[i]);
	free(p);
	return (NULL);
}

static size_t	split_strnum(char const *s, char *sep)
{
	size_t	counter;
	int		flag;

	flag = 0;
	counter = 0;
	while (*s)
	{
		if (!flag && !ft_strchr(sep, *s))
		{
			++counter;
			flag = 1;
		}
		else if (ft_strchr(sep, *s))
			flag = 0;
		s++;
	}
	return (counter);
}

char	**split(char const *s, char *separator)
{
	char	**p;
	size_t	arr_len;
	size_t	end;
	size_t	i;

	if (!s)
		return (NULL);
	arr_len = split_strnum(s, separator);
	p = ft_calloc(arr_len + 1, sizeof(*p));
	if (!p)
		return (NULL);
	i = -1;
	while (++i < arr_len)
	{
		end = 0;
		while (ft_strchr(separator, *s))
			s++;
		while (s[end] && !ft_strchr(separator, *s))
			end++;
		p[i] = ft_substr(s, 0, end);
		if (!p[i])
			return (split_clr(p));
		s += end;
	}
	return (p);
}
/*
#include <stdio.h>

int		main(void)
{
	char *str = "first \t\n               \ second \t\n          last     ";
	char **strs = split(str, "\t\n\ ");
	for (int i; strs[i]; i++)
		printf("|%s|\n", strs[i]);
	return 0;
}*/
