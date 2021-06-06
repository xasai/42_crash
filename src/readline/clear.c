#include "readline.h"

/*
**==================================================================
**	DESCRIPTION:
**		Clear all after and below of cursor.
*/
void	clear_after_cursor(void)
{
	static char	*ce;
	static char	*cd;

	if (!ce || !cd)
	{
		ce = tgetstr("ce", NULL);
		cd = tgetstr("cd", NULL);
	}
	tputs(ce, 1, putint);
	tputs(cd, 20, putint);
}
