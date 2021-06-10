#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*p;

	i = -1;
	p = s;
	while (++i < n)
		p[i] = (unsigned char)c;
	return (s);
}
