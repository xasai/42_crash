#include "minishell.h"

char	*_prompt(void)
{
	static char	*prompt;
	char		*hostname;
	char		*username;

	if (!prompt)
	{
		prompt = PROMPT;
		hostname = getenv("HOSTNAME");
		if (NULL == hostname)
			hostname = getenv("HOST");
		username = getenv("USER");
		if (NULL == username)
		{
			username = getenv("USERNAME");
			if (NULL == username)
				username = getenv("LOGNAME");
		}
		if (username && hostname)
			prompt = cat_lines_tab((char *[5]) \
			{username, "@", hostname, ": ", NULL});
	}
	return (prompt);
}

/*
** DESCRIPTION:
**	Initializing crash main struct in this function.
*/
t_shell	*init_term(char **envp)
{
	t_shell	*crash;

	crash = malloc(sizeof(*crash));
	if (NULL == crash)
		exit_message("Malloc Error init.c:7\n", SYS_ERROR);
	crash->envp = envp;
	crash->prompt = _prompt();
	return (crash);
}
