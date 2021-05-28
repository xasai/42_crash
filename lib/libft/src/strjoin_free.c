#include "libft.h"

char	*strjoin_free(const char *s1, const char *s2, char free_flag)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		new[i++] = s1[j++];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	if (free_flag)
	{
		free((void *)s1);
		free((void *)s2);
	}
	return (new);
}