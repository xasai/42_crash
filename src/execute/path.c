#include "minishell.h"

#define SHOW_DEBUG 0

#define DEBUG(...)\
	if (SHOW_DEBUG)\
	{\
		printf("Debug: %s():%d ", __FUNCTION__, __LINE__);\
		printf(__VA_ARGS__);\
	}
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
**	search_path searchs the binary in PATH environ variable
**	which is represented by null terminated array of strings g_sh->**path.
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
	DEBUG("$PATH = \"%s\"\n", crash_getenv("PATH", g_sh->envp));
	DEBUG("pathame = \"%s\"\n", pathname);
	env_path = g_sh->path;
	while (env_path[idx])
	{
		abs_path = cat_lines_tab((char *[4]) \
		{env_path[idx], "/", pathname, NULL});
		if (!abs_path)
			exit_message("Memory allocation failure", SYS_ERROR);
		DEBUG("Searching %s in %s[%lu] ...\n", abs_path, env_path[idx], idx);
		if (is_exist(abs_path))
		{
			free(pathname);
			DEBUG("SUCCESS\n");
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
**	get_path takes arg0 given to our shell.If it has slash character
**	arg0 will be returned. If there's no slash in arg0, get_path will
**	try to find arg0 file in PATH env variable. If such file was found
**	arg0 is freed, and new path to file is returned
**
** RETURN VALUE:
**	Path to file
**	If there's error whith memory allocation, program exits with status code 2.
*/
char	*get_path(char *arg0)
{
	if (!is_path(arg0))
		return (search_path(arg0));
	return (arg0);
}
