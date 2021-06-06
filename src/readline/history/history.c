#include "history.h"

bool	history(char *buf, t_lsthead **chrlst_head)
{
	if (!ft_strncmp(termcap()->k_up, buf, 3))
		;
	else if (!ft_strncmp(termcap()->k_down, buf, 3))
		;
	else
		return (false);
	(void)chrlst_head;
	return (true);
}
