#include "libft.h"

int	ft_intwid(long int i, int base)
{
	int	ret;

	ret = 0;
	if (i <= 0)
		ret++;
	while (i && ++ret)
		i /= base;
	return (ret);
}
