#include "minishell.h"

/*
 * Replaces the substring in the string with substr
 */
char	*strreplace(char *line, int start, int end, char *substr)
{
	int line_len;
	int substr_len;
	int newstr_len;
	char *newline;

	line_len = ft_strlen(line);
	if (line_len < start || line_len < end 	||	start > end)
		return (NULL);
	substr_len = ft_strlen(substr);
	newstr_len = line_len - (start - end) + substr_len;
	newline = ft_calloc(newstr_len, sizeof(char));
	if (newline == NULL)
		return (NULL);
	ft_memmove(newline, line, line_len - start);
	ft_memmove(&newline[start], substr, substr_len);
	ft_memmove(&newline[start + substr_len], &line[end], line_len - end);
	return (newline);
}
