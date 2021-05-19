#include "libft.h"

int	get_int_wid(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
		i += 1;
	while (n && ++i)
		n /= 10;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	int		sign;
	long	l;

	l = n;
	len = get_int_wid(n);
	s = malloc(sizeof(*s) * (len + 1));
	if (!s)
		return (NULL);
	if (l < 0)
	{
		sign = 1;
		l = -l;
		s[0] = '-';
	}
	else
		sign = 0;
	s[len] = '\0';
	while (len-- > sign)
	{
		s[len] = '0' + l % 10;
		l /= 10;
	}
	return (s);
}
