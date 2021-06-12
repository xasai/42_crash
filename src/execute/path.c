#include "minishell.h"

/*		
**=================================================
** DESCRIPTION: 
**	Function which takes path as parameter, and
**	check if it is a relative path;
**
** RETURN VALUE:
**	TRUE: if path is relative path.
**	FALSE: in other way.
*/
static bool	is_relative_path(char *path)
{
	return (path[0] != '/' && ft_strchr(path, '/'));
}

/*		
**=================================================
** DESCRIPTION: 
**	Function which takes path as parameter, and
**	check if it is a absolute path;
**
** RETURN VALUE:
**	TRUE: if path is absolute path.
**	FALSE: in other way.
*/
static bool	is_absolute_path(char *path)
{
	return (path[0] == '/');
}

/*		
**=================================================
** DESCRIPTION: 
**	Function which takes relative path as parameter, and
**	return it's absolute value.
**
** NOTE:
**	1st Parameter is freed inside function body.
**
** RETURN VALUE:
**	@char* absolute_path: if allocation succeed.
**	exit with explicit message, if memory allocation failed.
*/
char *reltoabs(char *rel_path)
{
	char	*cwd;
	char	*abs_path;
	
	cwd = _getcwd();
	if (!cwd)
		exit_message("Memory allocation failure", SYS_ERROR);
	abs_path = cat_lines_tab((char *[4]) \
				{cwd, "/", rel_path, NULL});
	if (!abs_path)
		exit_message("Memory allocation failure", SYS_ERROR);
	free(cwd);
	free(rel_path);
	return(abs_path);	
}

/*		
**=================================================
** DESCRIPTION: 
**	Takes name of binary and search this file in env_path table.
**	If there's no such file, return the original binary name.
**
** NOTE:
**	1st Parameter is freed inside function, if binary exists
**	in PATH variable.
**
** RETURN VALUE:
**	@char *absolute path: if file exists and allocation succeed.
**	exit with explicit message, if memory alloctation failed.
*/
static char	*search_path(char *pathname, char **env_path)
{
	size_t	idx;
	char	*abs_path;

	idx = 0;
	while (env_path[idx])
	{
		abs_path = cat_lines_tab((char *[4]) \
		{env_path[idx], "/", pathname, NULL});
		if (!abs_path)
			exit_message("Memory allocation failure", SYS_ERROR);
		if (is_exist(abs_path))
		{
			free(pathname);
			return (abs_path);
		}
		free(abs_path);
		idx++;
	}
	return (pathname);
}

/*		
**=================================================
** DESCRIPTION: 
**	Finds absolute path of file pathname, and returns it.
**	1st parameter can be:
**		1) Absolute path.
**		2) Relative path.
**		3) Name of binary in $PATH environ variable.
**	
** NOTE:
**	If absolute path is found, frees pathname pointer.	
**
** RETURN VALUE:
**	@char *absolute path: if allocation succeed.
**	exit with explicit message, if memory alloctation failed.
*/
char	*get_path(char *pathname, char **env_path)
{
	char	*path;

	if (is_absolute_path(pathname))
		;
	else if (is_relative_path(pathname))
		reltoabs(pathname);
	else if (env_path)
		path = search_path(pathname, env_path);
	return (path);
}
