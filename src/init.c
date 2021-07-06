#include "minishell.h"

t_shell	*g_sh;

static void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

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
	env = ft_calloc(sizeof(char **), env_counter);
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
**	Initialize g_sh->saved_stdin.
**	Initialize g_sh->saved_stdout.
**
** RETURN VALUE:
**		t_shell * : if initializing succeed.
**		exit : if initializing failed.
*/
void	init_sh(char **envp)
{
	setup_term();
	g_sh = ft_calloc(sizeof(*g_sh));
	if (NULL == g_sh)
		exit_message("Memory allocation failure", SYS_ERROR);
	g_sh->path = _path();
	g_sh->envp = _env(envp);
	g_sh->prompt = _prompt();
	g_sh->saved_stdout = dup(STDOUT_FILENO);
	g_sh->saved_stdin = dup(STDIN_FILENO);
	if (g_sh->saved_stdout == -1 || g_sh->saved_stdin == -1)
		exit_message("crash: dup() ", SYS_ERROR);
}
