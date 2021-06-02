#include "minishell.h"

void	specch_replace(t_dlist *l) //not used
{
	int i;
	int j;

	j = -1;
	i = -1;

	while (l)
	{
		while (l->name && l->name[++i])
		{
			if (l->name[i] == BCKSLSH_CH)
				l->name[i] = '\\';
			else if (l->name[i] == DBRCKT_CH)
				l->name[i] = '"';
			else if (l->name[i] == OBRCKT_CH)
				l->name[i] = '\'';
			else if (l->name[i] == SPC_CH)
				l->name[i] = ' ';
		}
		i = -1;
		while(l->arg && l->arg[++i])
			while(l->arg[i][++j])
			{
				if (l->arg[i][j] == BCKSLSH_CH)
					l->arg[i][j] = '\\';
				else if (l->arg[i][j] == DBRCKT_CH)
					l->arg[i][j] = '"';
				else if (l->arg[i][j] == OBRCKT_CH)
					l->arg[i][j] = '\'';
				else if (l->arg[i][j] == SPC_CH)
					l->arg[i][j] = ' ';
			}
		l = l->prev;
	}
}
