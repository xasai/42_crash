#include "minishell.h"

/*
 *  you can send only a dynamically allocated line
 */
char **lineptrjoin(char **ptr, char *line, char free_flag)
{
	char	**new_ptr;
	int		ptr_len;

	ptr_len = 0;
	if (ptr)
		while(ptr[ptr_len])
			++ptr_len;
	new_ptr = malloc(sizeof(char *) * (ptr_len + 2));
	if (!new_ptr)
		return NULL;
	new_ptr[ptr_len + 1] = NULL;
	new_ptr[ptr_len] = line;
	while(ptr && --ptr_len >= 0)
		new_ptr[ptr_len] = ptr[ptr_len];
	if (free_flag)
		free(ptr);
	return (new_ptr);
}
