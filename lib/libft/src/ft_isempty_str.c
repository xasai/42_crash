#include "libft.h"

int	ft_isempty_str(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str)
		return (0);
	else
		return (1);
}
