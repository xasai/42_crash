#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	i = -1;
	d = dest;
	s = src;
	while (++i < n)
		d[i] = s[i];
	return (d);
}
