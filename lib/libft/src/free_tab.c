#include "libft.h"

void	free_tab(void **tab)
{
	size_t	idx;

	if (!tab)
		return ;
	idx = 0;
	while (tab[idx])
		free(tab[idx++]);
	free(tab);
}
