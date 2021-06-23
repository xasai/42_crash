#include "libft.h"

char	*cat_lines_tab(char **lines)
{
	char	*line;
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (NULL != lines[i])
	{
		size += ft_strlen(lines[i]);
		i++;
	}
	line = ft_calloc(sizeof(*line), (size + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (NULL != *lines)
	{
		ft_strlcat(line, *lines, size + 1);
		lines++;
	}
	return (line);
}
