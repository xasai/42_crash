#include "minishell.h"

bool	isunclosedquotes(char *line)
{
	bool	*qout_flag;
	size_t	qout_count;

	qout_flag = (bool[2]){0};
	qout_count = 0;
	while (*line)
	{
		if (*line == '\"' && !qout_flag[1])
		{
			qout_flag[0] ^= true;
			++qout_count;
		}
		else if (*line == '\'' && !qout_flag[0])
		{
			qout_flag[1] ^= true;
			++qout_count;
		}
		++line;
	}
	if (qout_count % 2 == 0)
		return (false);
	else
		return (true);
}
