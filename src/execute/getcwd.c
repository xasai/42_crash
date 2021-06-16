#include "minishell.h"

#define BUFF_SIZE 32 

char	*_getcwd(void)
{
	char	*buf;
	size_t	size;
	
	size = BUFF_SIZE;
	buf = malloc(sizeof(*buf) * size);
	if (!buf)
		return (NULL);
	buf = getcwd(buf, size);
	while (buf == NULL && errno == ERANGE)
	{
		size += BUFF_SIZE;
		buf = getcwd(buf, size); 	
	}
	return (buf);
}
