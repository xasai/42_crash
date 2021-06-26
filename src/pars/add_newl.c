#include "minishell.h"

t_cmdlst	*add_newl(t_cmdlst *l)
{
	t_cmdlst *new_l;

	new_l = malloc(sizeof(t_cmdlst));
	if (!new_l)
		exit_message("Memory allocation failure", SYS_ERROR);
	*new_l = (t_cmdlst){.prev = l};//Такая инициализация занулит все кроме .prev
	// На счет поля prev, под сомнением, оно скорее всего никак не пригождается.
	if (l)
		l->next = new_l;
	return (new_l);
}
