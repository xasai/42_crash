#include "readline.h"

void	clear_after_cursor(void/*size_t cursor_pos, size_t line_len, size_t prompt_len*/)
{
	static char *ce;
	static char *cd;

	if (!ce || !cd)
	{
		ce = tgetstr("ce", NULL);
		cd = tgetstr("cd", NULL);
	}
	//tputs(termcap()->save_c, 1, putint);
	tputs(ce, 1, putint);
	//tputs(termcap()->move_down, 1, putint);
	//ft_putchar('\r');
	tputs(cd, 20, putint);
	//tputs(termcap()->move_up, 1, putint);
	//tputs(termcap()->restore_c, 1, putint);
}
