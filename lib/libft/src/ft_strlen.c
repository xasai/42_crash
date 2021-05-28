#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*(p++))
		;
	return (p - 1 - s);
}
