#include "pars.h"

void skip_spasech(char **line)
{
    while(ft_isspace(**line))
        ++*line;
}

size_t get_spasecount(char *line)
{
    size_t count;

    count = 0;
    while (ft_isspace(*line++))
        ++count;
    return (count);
}