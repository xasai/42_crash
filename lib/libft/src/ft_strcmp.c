#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	ret;

	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	ret = (int)*s1 - (int)*s2;
	return (ret);
}
