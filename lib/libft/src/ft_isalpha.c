#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c <= 'z' && 'a' <= c) || (c <= 'Z' && 'A' <= c));
}
