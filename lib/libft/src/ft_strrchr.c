#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	lo;
	int	i;

	lo = -1;
	i = -1;
	while (s[++i])
		if (s[i] == (unsigned char)c)
			lo = i;
	if (lo != -1)
		return ((char *)&s[lo]);
	if (c == 0)
		return ((char *)&s[i]);
	return (NULL);
}
