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

	substr_len = 0;
	line_len = ft_strlen(line);
	if (line_len < start || line_len < end 	||	start > end)
		return (NULL);
	if (substr)
		substr_len = ft_strlen(substr);
	newstr_len = line_len - 1 - (end - start) + substr_len;
	newline = ft_calloc(newstr_len + 1, sizeof(char));
	if (newline == NULL)
		return (NULL);
	ft_memmove(newline, line, start);
	ft_memmove(&newline[start], substr, substr_len);
	ft_memmove(&newline[start + substr_len], &line[end + 1], line_len - (end + 1));
	return (newline);
}
