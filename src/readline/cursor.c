#include "readline.h"

/*
**==================================================================
** DECRIPTION : 
**      Decrease cursor_pos value by 1 and move it 1 column left.
**      If cursor_pos <= 0 just leave.
*/
void	mov_left(t_rl_sizes *s)
{
	struct winsize	win_size;

	if (s->cursor_pos > 0)
	{
		if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win_size) < 0)
			exit_message("Ioctl() function bad return", SYS_ERROR);
		if (((s->prompt_len + s->cursor_pos + 1) % win_size.ws_col) == 1)
		{
			tputs(termcap()->move_up, 1, putint);
			while (win_size.ws_col--)
				tputs(termcap()->move_right, 1, &putint);
		}
		else
			tputs(termcap()->move_left, 1, &putint);
		s->cursor_pos--;
	}
}

/*
**==================================================================
** DECRIPTION : 
**      Increase cursor_pos value by 1 and move it 1 column right.
**      If cursor_pos >= line_len just leave.
*/
void	mov_right(t_rl_sizes *s)
{
	struct winsize	win_size;

	if (s->cursor_pos < s->line_len)
	{
		if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win_size) < 0)
			exit_message("Ioctl() function bad return", SYS_ERROR);
		if (!((s->prompt_len + s->cursor_pos + 1) % win_size.ws_col))
		{
			tputs(termcap()->move_down, 1, putint);
			putint('\r');
		}
		else
			tputs(termcap()->move_right, 1, &putint);
		s->cursor_pos++;
	}
}

/*
**==================================================================
** DECRIPTION : 
**     	Decrease cursors position by 1, then delete char under it.
**		Frees chrlst element.
**      If cursor_pos == 0 just leave.
*/
static void	backspace(t_lsthead *chrlst_head, t_rl_sizes *s)
{
	if (s->cursor_pos > 0)
	{
		mov_left(s);
		tputs(termcap()->delete_char, 1, &putint);
		del_chrlst(chrlst_head, s->cursor_pos);
		s->line_len--;
		rl_rewrite(chrlst_head, s);
	}
}

/*
**==================================================================
** PATH: src/readline/cursor.c
**
** DESCRIPTION :
**      Check if in line ARROW [right | left] or backspace key.
**      If there is, then call corresponding function:
**      mov_left(), mov_right(), backspace().
**
** RETURN VALUE
**      TRUE:   if there was a any of these keys
**      FALSE:  if there was not any of these keys
**/
bool	cursor_mov(char *buf, t_lsthead *chr_head, \
		t_rl_sizes *s)
{
	if (!ft_strncmp(buf, termcap()->k_left, 3))
		mov_left(s);
	else if (!ft_strncmp(buf, termcap()->k_right, 3))
		mov_right(s);
	else if (!ft_strncmp(buf, termcap()->k_backspace, 3))
		backspace(chr_head, s);
	else
		return (false);
	return (true);
}
