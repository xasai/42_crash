#include "libft.h"

char	*ft_substr(char const *s, unsigned int start,
			size_t len)
{
	int		i;
	char	*new;

	if (!s)
		return (NULL);
	i = 0;
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	while (s[start] && len--)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}
