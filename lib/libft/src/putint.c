#include "libft.h"

int	putint(int c)
{
	c = (unsigned char)c;
	return (write(1, &c, 1));
}
