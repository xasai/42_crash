#include "minishell.h"

char	*getenv_name(char *varstr)
{
	char	*name;	
	size_t	size;

	size = 0;
	if (ft_isalpha(varstr[size]) || varstr[size] == '_')
		size++;
	else
		return (NULL);
	while (ft_isalnum(varstr[size]) || varstr[size] == '_')
		size++;
	name = ft_substr(varstr, 0, size);
	return (name);
}
