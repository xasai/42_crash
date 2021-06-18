#include "libft.h"

void	free_tab(void **tab)
{
	size_t	idx;

	idx = 0;
	while (tab[idx])
		free(tab[idx++]);
	free(tab);
}
