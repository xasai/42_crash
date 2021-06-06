#include "minishell.h"
#include "pars.h"

void	replace(char *str, int i)
{
	if (str[i] == BCKSLSH_CH)
		str[i] = '\\';
	else if (str[i] == DOLLAR_CH)
		str[i] = '&';
	else if (str[i] == SPC_CH)
		str[i] = ' ';
	else if (str[i] == '$')
		/*env_past*/(void)i;
}
void	specch_replace(t_dlist *l) //not used
{
	int i;
	int j;

	i = -1;
	while (l)
	{
		while (l->name && l->name[++i])
			replace(l->name, i);
		i = -1;
		while(l->arg && l->arg[++i])
		{
			j = -1;
			while(l->arg[i][++j])
				replace(l->arg[i], j);
		}
		l = l->prev;
	}
}
