#include "libft.h"

int	ft_skip_atoi(char **s)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while (ft_isspace(**s))
		(*s)++;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	while (ft_isdigit(**s))
	{
		i = i * 10 + ft_ctod(**s);
		(*s)++;
	}
	return (i * sign);
}
