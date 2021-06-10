#include "libft.h"

void split_str(const char *line,char const **sep, char ***ptr, int word)
{
	int count;

	count = 0;
	while(*line && ft_strchr(*sep, *line))
		++line;
	while(line[count] && !ft_strchr(*sep, line[count]))
		++count;
	if (!*line)
	{
		(*ptr) = malloc(sizeof(*ptr) * (word + 1));
		if ((*ptr))
		{
			(*ptr)[word] = NULL;
			return;
		}
	}
	else
		split_str(line + count, sep, ptr, word + 1);
	if ((*ptr) && *sep)
		(*ptr)[word] = ft_substr(line, 0, count);
	if(*sep && (*ptr) && !(*ptr)[word])
		*sep = NULL;
}

char	**split_with_brckt(char const *line, char const *sep)
{
	char	**ptr;
	int i;

	i = 0;
	if (!line || !sep)
		return (NULL);
	ptr = NULL;
	split_str(line, &sep, &ptr, 0);
	if (sep == NULL)
	{
		while(ptr && ptr[i])
			free(ptr[i++]);
		free(ptr);
	}
	return (ptr);
}