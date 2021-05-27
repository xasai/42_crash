#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		putchar_fd('-', fd);
		n *= -1;
	}
	if (n < 10 && n >= 0)
	{
		putchar_fd(n + '0', fd);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	ft_putnbr_fd(n % 10, fd);
}
