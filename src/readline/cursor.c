#include "readline.h"

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
bool	cursor_mov(char *line, t_lsthead *chr_head, size_t *cursor_pos)
{
	if (!ft_strncmp(line, termcap()->k_left, 3))
		mov_left(cursor_pos);
	else if (!ft_strncmp(line, termcap()->k_right, 3))
		mov_right(chr_head->size, cursor_pos);
	else if (!ft_strncmp(line, termcap()->k_backspace, 3))
		backspace(chr_head, cursor_pos);
	else
		return (false);
	return (true);
}

/*
**==================================================================
** DECRIPTION : 
**     	Decrease cursors position by 1, then delete char under it.
**		Frees chrlst element.
**      If cursor_pos == 0 just leave.
*/
void	backspace(t_lsthead *chrlst_head, size_t *cursor_pos)
{
	t_chrlst	*current;
	t_chrlst	*prev;
	t_chrlst	*next;
	size_t		i;

	i = 0;
	current	= chrlst_head->head;
	while (++i < *cursor_pos)	
		current = current->next;
	if (*cursor_pos > 0)
	{
		prev = current->prev;
		next = current->next;
		if (next)
			next->prev = prev;
		if (prev)
			prev->next = next;
		if (*cursor_pos <= 1)
			chrlst_head->head = next; 
		free(current);
		mov_left(cursor_pos);
		tputs(termcap()->delete_char, 1, &putint);
		chrlst_head->size--;
	}
}

/*
**==================================================================
** DECRIPTION : 
**      Decrease cursor_pos value by 1 and move it 1 column left.
**      If cursor_pos <= 0 just leave.
*/
void	mov_left(size_t *cursor_pos)
{
	if (*cursor_pos > 0)
	{
		tputs(termcap()->move_left, 1, &putint);
		(*cursor_pos)--;
	}
}

/*
**==================================================================
** DECRIPTION : 
**      Increase cursor_pos value by 1 and move it 1 column right.
**      If cursor_pos >= line_len just leave.
*/
void	mov_right(size_t line_len, size_t *cursor_pos)
{
	if (*cursor_pos < line_len)
	{
		tputs(termcap()->move_right, 1, &putint);
		(*cursor_pos)++;
	}
}

