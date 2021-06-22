#include "minishell.h"

t_shell	*g_sh;

/*	
**=================================================
** DESCRIPTION:
**	Generate prompt for our g_shell g_sh
**
** RETURN VALUE: 
**	prompt: if allocation succeed.
**	exit: if allocation failed.
*/
static char	*_prompt(void)
{
	static char	*prompt;
	char		*hostname;
	char		*username;

	if (!prompt)
	{
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
		else
			prompt = ft_strdup(PROMPT);
	}
	if (!prompt)
		exit_message("Memory allocation failure", SYS_ERROR);
	return (prompt);
}

/*
** DESCRIPTION:
**	Allocate copy of **environ variable. 
**
** RETURN VALUE:
**	environ tab: if allocation succeed.
**	exit : if allocation failed.
*/
static char	**_env(char **envp)
{
	char	**env;
	size_t	env_counter;
	size_t	idx;

	env_counter = 0;
	while (envp[env_counter++])
		;
	env = malloc(sizeof(char **) * env_counter);
	if (!env)
		exit_message("Memory alloction failure", SYS_ERROR);
	idx = 0;
	while (envp[idx])
	{
		env[idx] = ft_strdup(envp[idx]);
		if (!env[idx])
			exit_message("Memory alloction failure", SYS_ERROR);
		idx++;
	}
	return (env);
}

/*
** DESCRIPTION:
**	Split $PATH environ variable on strings in **tab variable.
**
** RETURN VALUE:
**	path tab: if allocation succeed.
**	NULL: if allocation failed.
*/
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
**	Allocating (t_shell *) on heap, 
**	Initialize on heap (char *) t_shell->prompt for readline.
**	Initialize on heap (char **) t_shell->env for future adding environ variables.
**	Initialize on heap (char **) t_shell->path tab.
**
** RETURN VALUE:
**		t_shell * : if initializing succeed.
**		exit : if initializing failed.
*/
void	init_term(char **envp)
{
	g_sh = malloc(sizeof(*g_sh));
	if (NULL == g_sh)
		exit_message("Malloc Error init.c:7\n", SYS_ERROR);
	g_sh->path = _path();
	g_sh->envp = _env(envp);
	g_sh->prompt = _prompt();
}
