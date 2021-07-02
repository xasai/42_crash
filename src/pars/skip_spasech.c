#include "pars.h"

void skip_spasech(char **line)
{
    while(ft_isspace(**line))
        ++*line;
}
