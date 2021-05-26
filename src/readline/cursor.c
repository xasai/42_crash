#include "readline.h"

/*  readline/CURSOR.c */

/*
** DESCRIPTION :
**      Check if in line ARROW - up | down | right | left
**      or backspace key. If there call corresponding function.
**
** RETURN VALUE
**      TRUE:   if there was a any of these keys
**      FALSE:  if there was not any of these keys
**/
bool	cursor_key(char *line, size_t *line_len, size_t *cursor_pos)
{
	struct s_terminfo *ti;

	ti = &g_shell->terminfo;
	if (!ft_strncmp(line, ti->k_left, 3))
		mov_left(cursor_pos);
	else if (!ft_strncmp(line, ti->k_right, 3))
		mov_right(*line_len, cursor_pos);
	else if (!ft_strncmp(line, ti->k_backspace, 3))
		; /* backspace() */
	else
		return (false);
	return (true);
}

/*
** DECRIPTION : 
**      Decrease cursor_pos value by 1 and move it 1 column left.
**      If cursor_pos <= 0 just leave.
*/
void	mov_left(size_t *cursor_pos)
{
	if (*cursor_pos > 0)
	{
		tputs(cursor_left, 1, &putint);
		(*cursor_pos)--;
	}
}

/*
** DECRIPTION : 
**      Increase cursor_pos value by 1 and move it 1 column right.
**      If cursor_pos >= line_len just leave.
*/
void	mov_right(size_t line_len, size_t *cursor_pos)
{
	if (*cursor_pos < line_len)
	{
		tputs(cursor_right, 1, &putint);
		(*cursor_pos)++;
	}
}
