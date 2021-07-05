#include "minishell.h"

void *xalloc(size_t count, size_t size)
{
    void	*p;

    p = malloc(size * count);
    if (p == NULL)
        exit_message("Memory allocation failure", SYS_ERROR);
    ft_bzero(p, size * count);
    return (p);
}

