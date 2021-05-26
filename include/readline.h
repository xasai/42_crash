#ifndef READLINE_H
# define READLINE_H

# include "minishell.h"
# include "stdbool.h"

char		*readline(const char *prompt);

bool		control_char(char *line);

/*  readline/CURSOR.c */

/*
** DESCRIPTION : 
**		Check if in line ARROW - up | down | right | left
** 		or backspace key. If there call corresponding function.
**
** RETURN VALUE
**		TRUE:	if there was a any of these keys 
**		FALSE:	if there was not any of these keys 
**/
bool		cursor_key(char *line, size_t *line_len, size_t *cursor_pos);

/*
** DECRIPTION : 
**		Decrease cursor_pos value by 1 and move it 1 column left.
**		If cursor_pos <= 0 just leave.
*/
void		mov_left(size_t *cursor_pos);

/*
** DECRIPTION : 
**		Increase cursor_pos value by 1 and move it 1 column right.
**		If cursor_pos >= line_len just leave.
*/
void		mov_right(size_t line_len, size_t *cursor_pos);

/*
** DECRIPTION :  FIXME FIXME FIXME FIXME FIXME
**	
**		
*/
void		backspace(void);

#endif /* READLINE_H */
