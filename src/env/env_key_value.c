#include "minishell.h"

size_t	get_envkey_len(char *line)
{
	int	envkey_len;

	envkey_len = 1;
	if (ft_isalpha(line[envkey_len]) || line[envkey_len] == '_')
		++envkey_len;
	else if (line[envkey_len] == '?')
		return (2);
	while (ft_isalnum(line[envkey_len]) || line[envkey_len] == '_')
		++envkey_len;
	return (envkey_len);
}

size_t	get_envvalue_len(char *line, size_t envkey_len)
{
	size_t	envvalue_len;
	char	*envvalue;
	char	*envkey;

	envkey = ft_substr(line, 1, envkey_len - 1);
	if (envkey == NULL)
		exit_message("Memory allocation failure", SYS_ERROR);
	else if (*envkey == '?' || *envkey == 0)
	{
		free(envkey);
		return (ft_intwid(g_sh->exit_status, 10));
	}
	envvalue = crash_getenv(envkey);
	free(envkey);
	if (envvalue == NULL)
		return (0);
	envvalue_len = ft_strlen(envvalue);
	return (envvalue_len);
}
