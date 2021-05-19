#include "libft.h"

void	*ft_memccpy(void *dest, const void *src,
		int c, size_t n)
{
	unsigned int		i;
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	i = -1;
	dest = NULL;
	while (++i < n)
	{
		d[i] = s[i];
		if (d[i] == (unsigned char)c)
		{
			dest = &d[++i];
			break ;
		}
	}
	return (dest);
}
