#include "libft.h"

void	ft_putnbr_base(long int i, const char *base)
{
	long	len;

	len = ft_strlen(base);
	if (i < 0)
	{
		i = -i;
		write(1, "-", 1);
	}
	if (i > len)
	{
		ft_putnbr_base(i / len, base);
		ft_putnbr_base(i % len, base);
	}
	else if (i < len)
	{
		write(1, &base[i], 1);
	}
}
