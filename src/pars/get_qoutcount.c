#include "minishell.h"

size_t	get_qoutcount(char *line, size_t arg_len)
{
	size_t	count;

	count = 0;
	while (*line && arg_len--)
	{
		if (*line == DQUOT_CH || *line == QUOT_CH)
			++count;
		++line;
	}
	return (count);
}
