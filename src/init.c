#include "minishell.h"

/*	Generate prompt of crash */
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

/* Generate $PATH as table of strings */
char	**_path(void)
{
	char	*path;
	char	**tab;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	tab = ft_split(path, ':');
	return (tab);
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
	crash->path = _path();
	return (crash);
}
