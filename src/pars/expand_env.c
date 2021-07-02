#include "minishell.h"

int	get_envkey_len(char *line)
{
	int envkey_len;

    envkey_len = 0;
	if (ft_isalpha(line[envkey_len]) || line[envkey_len] == '_')
		++envkey_len;
	else if (line[envkey_len] == '?')
		return (1);
	while(ft_isalnum(line[envkey_len]) || line[envkey_len] == '_')
		++envkey_len;
	return (envkey_len);
}

void	expand_env(char **line, int start, int env_flag)
{
	int		var_len;
	char	*var_substr;
	char	*var_name;
	char	*free_line;

	free_line = *line;
	var_len = get_envkey_len(&(*line)[start + 1]);
	var_name = ft_substr(*line, start + 1, var_len);
	if (var_name[0] == '?' && !var_name[1])
		var_substr = ft_itoa(g_sh->exit_status);
	else 
		var_substr = crash_getenv(var_name);
	free(var_name);
	*line = strreplace(*line, start, start + var_len, var_substr);
	if (env_flag > 1)
		free(free_line);
}
