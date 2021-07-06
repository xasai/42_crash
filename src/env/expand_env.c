#include "minishell.h"

void	expand_env(char *buffer, char *line)
{
	size_t	envkey_len;
	char	*envvalue;
	char	*envkey;

	envkey_len = get_envkey_len(line);
	envkey = ft_substr(line, 1, envkey_len - 1);
	if (envkey == NULL)
		exit_message("Memory allocation failure", SYS_ERROR);
	if (*envkey == '?')
	{
		envvalue = ft_itoa(g_sh->exit_status);
		if (envvalue == NULL)
			exit_message("Memory allocation failure", SYS_ERROR);
	}
	else if (*envkey == '\0')
		envvalue = "$";
	else
		envvalue = crash_getenv(envkey);
	if (envvalue != NULL)
		ft_memmove(buffer, envvalue, ft_strlen(envvalue));
	if (*envkey == '?')
		free(envvalue);
	free(envkey);
}
