#include "minishell.h"

#define SHOW_DEBUG 0

/*
**=================================================
** DESCRIPTION: 
**	is_path takes char * argument and
**	trying to find slash character in it
**
** RETURN VALUE:
**	TRUE:	if slash in str.
**	FALSE:	if no slash in str.
*/
inline static bool	is_path(char *str)
{
	return (ft_strchr(str, '/') != NULL);
}

/*              
**=================================================
** DESCRIPTION: 
**	is_exist takes absolute path to file and check 
**	if such file exists using function stat(2). 
**
** RETURN VALUE:
**      TRUE:	if file exists. 
**      FALSE:	if there is no such file.
*/
inline static bool	is_exist(char *path_to_file)
{
	struct stat	buf;

	return (stat(path_to_file, &buf) == 0);
}

/*		
**=================================================
** DESCRIPTION: 
**	search_path searchs the binary in PATH environ variable which 
**	is represented by null terminated array of strings (char **)g_sh->path.
**
** NOTE:
**	1st Parameter is freed inside function, if binary exists
**	in one PATH's path.
**
** RETURN VALUE:
**	Return allocated pointer to absolute path value if it exists.
**	Return its 1st argument if no such file in PATH variable.
**	If there's error whith memory allocation, program exits with status code 2.
*/
static char	*search_path(char *pathname)
{
	size_t	idx;
	char	*abs_path;
	char	**env_path;

	idx = 0;
	env_path = g_sh->path;
	while (env_path[idx])
	{
		abs_path = cat_lines_tab((char *[4]) \
		{env_path[idx], "/", pathname, NULL});
		if (!abs_path)
			exit_message("Memory allocation failure", SYS_ERROR);
		if (is_exist(abs_path))
			return (abs_path);
		free(abs_path);
		idx++;
	}
	return (NULL);
}

/*		
**=================================================
** DESCRIPTION: 
**	get_path takes arg0 given to our shell. If it has slash character
**	arg0 will be returned. If there's no slash in arg0, get_path will
**	try to find arg0 file in PATH env variable.
**
** RETURN VALUE:
**	Path to file
**	If no file found in $PATH return NULL.
**	If there's error whith memory allocation, program exits with status code 2.
*/
char	*get_path(char *arg0)
{
	char	*abs_path;

	if (NULL == arg0)
		return (NULL);
	if (is_path(arg0))
		return (ft_strdup(arg0));
	abs_path = search_path(arg0);
	if (!abs_path)
	{
		putstr_fd(arg0, STDERR_FILENO);
		putendl_fd(": command not found", STDERR_FILENO);
		g_sh->exit_status = 0x7f;
		return (NULL);
	}
	return (abs_path);
}
