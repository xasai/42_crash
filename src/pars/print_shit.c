#include "pars.h"
#include "stdio.h"

void print_this_shit(t_cmdlst *l)
{
	while(l->prev)
		l = l->prev;
	while(l)
	{
		printf("\tName \"%s\"\n", l->pathname);
		if (l->args)
		{
			for (int i = 0; l->args[i]; ++i)
				printf("\targv[%i] \"%s\"\n", i, l->args[i]);
		}
		if (l->sepch)
			printf("\tsepch %c\n", l->sepch);
		l = l->next;
	}
}
