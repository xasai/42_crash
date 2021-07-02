#include "minishell.h"

int	get_envkey_len(char *line)
{
	int envkey_len;

    envkey_len = 1;
	if (ft_isalpha(line[envkey_len]) || line[envkey_len] == '_')
		++envkey_len;
	else if (line[envkey_len] == '?')
		return (2);
	while(ft_isalnum(line[envkey_len]) || line[envkey_len] == '_')
		++envkey_len;
	return (envkey_len);
}
