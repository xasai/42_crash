#include "pars.h"

/*
** DESCRIPTION:
**      The sstrlen() function calculates the length of the substring of 's',
**      'start' - index of the beginning of the substing, 'end' - of the end,
**      excluding symbol pointed to 'ignored' and the terminating null byte ('\0').
**      Returned length of the substring.
*/

size_t sstrlen(char *s, char *ignored, size_t start, size_t end)
{
    size_t count;

    count = 0;
    if (start > end)
        return (0);
    while (s[start] && start != end)
        if (!ft_strchr(ignored, s[start]))
            ++count;
    return (count);
}