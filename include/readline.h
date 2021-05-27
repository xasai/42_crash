#ifndef READLINE_H
# define READLINE_H

# include "minishell.h"

# define BUFF_SIZE 3

typedef struct s_chrlst
{
	char	 		chr;
	struct s_chrlst *next;
	struct s_chrlst *prev;
}					t_chrlst;

typedef struct s_lsthead
{
	void		*head;
	size_t		size;
}				t_lsthead;

/*  PATH: src/readline/readline.c */
/*
** DESCRIPTION:
**	FIXME FIXME FIXME
**
*/
char		*readline(const char *prompt);

/*
** DESCRIPTION:
**      This function insert one new node in chr_lst linked list.
**      New node initialized on heap, and take a place as 
**      cursor_pos index node.
**  
**      Program exits if initialization of new node failed.
*/
void    rl_insert_chr(char chr, t_lsthead *chrlst_head, size_t *cursor_pos);

/*
** DESCRIPTION:
**      This function clear all to cursor's right, and rewrite it to STDOUT
**
** NOTE:
**      New char read placed at cursor_pos - 1.
**
*/
void    rl_rewrite(t_lsthead *chrlst_head, size_t cursor_pos);

char	*rl_cat_line(t_lsthead *chrlst_head);
/*  PATH: src/readline/cursor.c */

/*
** DESCRIPTION : 
**		Check if in line ARROW [right | left] or backspace key.
** 		If there is, then call corresponding function:
**		mov_left(), mov_right(), backspace().
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

/* PATH: src/readline/chrlst.c */

/*
** DESCRIPTION:
**      This function allocates one node of t_chrlst linked list.
**      Assigns its chr field to chr.
**      Assigns both prev and next pointers to NULL.
** RETURN VALUE
**      NEW_NODE:   if allocation succeed.
**      NULL:       if allocation fails.
*/
t_chrlst    *init_chrlst(char chr);

#endif /* READLINE_H */
