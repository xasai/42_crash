#include "minishell.h"
/*              
**=================================================
** DESCRIPTION: 
**      Function which takes absoule path as a parameter, and
**      check if such file exists. 
**
** RETURN VALUE:
**      TRUE: if file exists. 
**      FALSE: in other way.
*/
inline bool	is_exist(char *path_to_file)
{
	struct stat	buf;

	return (stat(path_to_file, &buf) == 0);
}
