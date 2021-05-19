#include "libft.h"

int	ft_isspace(int c)
{
	return ((c > 8 && c < 14) || c == 32);
}
