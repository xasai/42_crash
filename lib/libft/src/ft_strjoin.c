#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	k = 0;
	while (*s1)
		new[k++] = *s1++;
	while (*s2)
		new[k++] = *s2++;
	new[k] = '\0';
	return (new);
}
