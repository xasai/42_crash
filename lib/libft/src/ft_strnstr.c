#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (*big && len)
	{
		while (little[i] && big[i] == little[i] && (len - i) > 0)
			i++;
		if (!little[i])
			return ((char *)big);
		i = 0;
		big++;
		len--;
	}
	return (NULL);
}
