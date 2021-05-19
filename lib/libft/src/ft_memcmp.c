#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p1;
	const unsigned char	*p2;

	i = -1;
	p1 = s1;
	p2 = s2;
	while (++i < n)
		if (p1[i] != p2[i])
			return ((int)(p1[i] - p2[i]));
	return (0);
}
