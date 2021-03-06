#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	num;
	int		sign;

	sign = 1;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 7 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*(nptr++) == '-')
			sign = -1;
	}
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	return (sign * (int)num);
}
