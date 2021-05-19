#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	unsigned int		i;

	i = -1;
	src = s;
	while (++i < n)
		if (src[i] == (unsigned char)c)
			return ((void *)&src[i]);
	return (NULL);
}
