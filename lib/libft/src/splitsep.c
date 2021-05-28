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

static size_t	split_strnum(char const *s, char const *sep)
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

char	**splitsep(char const *line, char const *sep)
{
	char	**ptr;
	size_t	word_count;
	size_t	end;
	size_t	i;

	if (!line)
		return (NULL);
    word_count = split_strnum(line, sep);
    ptr = ft_calloc(word_count + 1, sizeof(*ptr));
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < word_count)
	{
		end = 0;
		while (ft_strchr(sep, *line))
			line++;
		while (line[end] && !ft_strchr(sep, line[end]))
            end++;
        ptr[i] = ft_substr(line, 0, end);
		if (!ptr[i])
			return (split_clr(ptr));
		line += end;
	}
	return (ptr);
}
