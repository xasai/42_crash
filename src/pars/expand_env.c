#include "minishell.h"

static int	env_len(char *line)
{
	int var_len;

	var_len = 0;
	if (ft_isalpha(line[var_len]) || line[var_len] == '_')
		++var_len;
	else if (line[var_len] == '?')
		return (1);
	while(ft_isalnum(line[var_len]) || line[var_len] == '_')
		++var_len;
	return (var_len);
}

void	expand_env(char **line, int start, int env_flag)
{
	int		var_len;
	char	*var_substr;
	char	*var_name;
	char	*free_line;

	free_line = *line;
	var_len = env_len(&(*line)[start + 1]);
	var_name = ft_substr(*line, start + 1, var_len);
	var_substr = crash_getenv(var_name);
	free(var_name);
	*line = strreplace(*line, start, start + var_len, var_substr);
	if (env_flag > 1)
		free(free_line);
}
