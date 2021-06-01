#ifndef READLINE_H
# define READLINE_H

# include "minishell.h"
# include "s_terminfo.h"
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

/*
**==================================================================
** PATH: src/readline/readline.c
**
** DESCRIPTION: FIXME
**		
**
*/
char	*readline(char *prompt);

/*
**==================================================================
** PATH: src/readline/readline.c
**
** DESCRIPTION:
**      This function insert one new node in chr_lst linked list.
**      New node initialized on heap, and take a place as 
**      cursor_pos index node.
**      Increase cursor_pos by 1.
**      Increase chrlst_head->size by 1.
**      Assign chrlst_head->head if neccessary.
**  
**      Program exits if initialization of new node failed.
*/
void    rl_insert_chr(char chr, t_lsthead *chrlst_head, size_t *cursor_pos);

/*
**==================================================================
** PATH: src/readline/readline.c
**
** DESCRIPTION:
**      Rewrite all after cursor.
*/
void    rl_rewrite(t_lsthead *chrlst_head, size_t cursor_pos);

/*
**==================================================================
** PATH: src/readline/readline.c
**
** DESCRIPTION:
**		Allocate list size * sizeof(char) bytes.
**		Concatenate all lists' chr to string.
**
**	RETURN VALUE
**		Pointer to string read by readline function
**		NULL if allocation
*/
char	*rl_cat_line(t_lsthead *chrlst_head);

/*
**==================================================================
** PATH: src/readline/cursor.c
**
** DESCRIPTION : 
**		Check if in line ARROW [right | left] or backspace key.
** 		If there is, then call corresponding function:
**		mov_left(), mov_right(), backspace().
**
** RETURN VALUE
**		TRUE:	if there was a any of these keys 
**		FALSE:	if there was not any of these keys 
**/
bool	cursor_mov(char *line, t_lsthead *chr_head, size_t *cursor_pos);

/*
**==================================================================
** PATH: src/readline/cursor.c
**
** DECRIPTION : 
**		Decrease cursor_pos value by 1 and move it 1 column left.
**		If cursor_pos <= 0 just leave.
*/
void	mov_left(size_t *cursor_pos);

/*
**==================================================================
** PATH: src/readline/cursor.c
**
** DECRIPTION : 
**		Increase cursor_pos value by 1 and move it 1 column right.
**		If cursor_pos >= line_len just leave.
*/
void	mov_right(size_t line_len, size_t *cursor_pos);

/*
**==================================================================
** PATH: src/readline/cursor.c
**
** DECRIPTION :
**		Decrease cursor position by 1, then delete char under it.
**      Frees chrlst element.
**		If cursor_pos == 0 just leave.
*/
void	backspace(t_lsthead *chrlst_head, size_t *cursor_pos);

/*
**==================================================================
** PATH: src/readline/chrlst.c
**
** DESCRIPTION:
**      This function allocates new node of t_chrlst linked list.
**      Assigns its chr field to chr.
**      Assigns both prev and next fields to NULL.
** RETURN VALUE
**      NEW_NODE:   if allocation succeed.
**      NULL:       if allocation fails.
*/
t_chrlst	*init_chrlst(char chr);

/*
**==================================================================
** PATH: src/readline/chrlst.c
**
** DESCRIPTION:
**		Function to free all t_chrlst elements in linked list.
*/
void	free_chrlst(t_chrlst *head);

/*
**==================================================================
** PATH: src/readline/termios.c
**
** DESCRIPTION:
**  On first call of this function, it is initializining all capability
**  we need in struct s_terminfo.
**  Return pointer to that struct
*/
struct s_terminfo	*termcap(void);

/*
**==================================================================
** PATH: src/readline/termios.c
**
** DESCRIPTION:
**  Initialize readline(rl) INPUT OUTPUT stream preferences. 
*/
void				termios_init(void);

/*
**==================================================================
** PATH: src/readline/termios.c
**
** DESCRIPTION:
**  Restore to system's INPUT OUTPUT stram preferences.
*/

void				termios_restore(void);

#endif /* READLINE_H */
