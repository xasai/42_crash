#include "readline.h"

/*
** DESCRIOPTION: FIXME FIXME FIXME
*/
	
char	*readline(const char *prompt)
{
	ssize_t		size;	
	size_t		cursor_pos;
	char		line_buf[BUFF_SIZE + 1];
	char		*line;
	t_lsthead	chrlst_head;
	
	termios_init();
	putstr_fd((char *)prompt, STDOUT_FILENO);
	size = 1;
	cursor_pos = 0;
	chrlst_head = (t_lsthead){0};
	line_buf[0] = 0;
	while (size && !ft_strchr(line_buf, '\n'))
	{
		size = read(STDIN_FILENO, line_buf, BUFF_SIZE);
		line_buf[size] = '\0';
		if (cursor_key(line_buf, &chrlst_head, &cursor_pos)) /* Check if cursor mov */
			continue ;
		else if (false) /* FIXME: Check if control char */
			continue ;
		else if (false) /* FIXME: Check if up/down arrow */
			continue ;
		rl_insert_chr(*line_buf, &chrlst_head, &cursor_pos);
		rl_rewrite(&chrlst_head, cursor_pos);
		line = rl_cat_line(&chrlst_head);
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_shell->old_termios) < 0)
		exit_message("Could not set interface attributes", 1);
	return (line);
}

/*
** DESCRIPTION:
**		This function rewrite all after cursor.
**		
*/
void	rl_rewrite(t_lsthead *chrlst_head, size_t cursor_pos)
{
	t_chrlst			*cur;		
	size_t				i;
	struct 	s_terminfo *ti;

	i = 0;
	cur = chrlst_head->head;
	ti = &g_shell->terminfo;
	tputs(ti->save_c, 1, &putint);
	if (cursor_pos == chrlst_head->size) /* skip if nothing to rewrite */
		return ;
	while (i++ < cursor_pos)
		cur = cur->next;
	while (cur)
	{
		putchar_fd(cur->chr, STDOUT_FILENO);
		cur = cur->next;
		i++;
	}
	tputs(ti->restore_c, 1, &putint);
}

/*
** DESCRIPTION:
**		This function insert one new node in chr_lst linked list.
**		New node initialized on	heap, and take a place as 
**		cursor_pos index node.
**		Increase cursor_pos by 1.
**		Increase chrlst_head->size by 1.
**		Assign chrlst_head->head if neccessary.
**	
**		Program exits if initialization of new node failed.
*/
void	rl_insert_chr(char chr, t_lsthead *chrlst_head, size_t *cursor_pos)
{
	t_chrlst	*new_node;	
	t_chrlst	*cur_node;
	size_t		i;
	
	i = 0;
	new_node = init_chrlst(chr);
	if (!new_node)
		exit_message("Malloc failure", EXIT_FAILURE);
	cur_node = chrlst_head->head;
	if (*cursor_pos != 0)
	{
		while (i++ < *cursor_pos - 1)
			cur_node = cur_node->next;	
		new_node->next = cur_node->next;	
		new_node->prev = cur_node;
		cur_node->next = new_node;
	}
	else
	{
		new_node->next = chrlst_head->head;
		chrlst_head->head = new_node;
	}
	putchar_fd(chr, STDOUT_FILENO);
	chrlst_head->size++;
	(*cursor_pos)++;	
}

/*
** PATH: src/readline/readline.c
**
** DESCRIPTION:
**      Allocate list size * sizeof(char) bytes.
**      Concatenate all lists' chr to string.
**
**  RETURN VALUE
**      Pointer to string read by readline function
**      NULL if allocation
*/
char	*rl_cat_line(t_lsthead *chrlst_head)
{
	t_chrlst	*cur;
	t_chrlst	*next;
	char		*line;	
	size_t		i;

	i = 0;
	cur = chrlst_head->head;
	line = malloc(sizeof(*line) * (chrlst_head->size + 1));
	if (!line)
		return (NULL);
	while (cur)
	{
		line[i++] = cur->chr;
		next = cur->next;	
		//free(cur);
		cur = next;	
	}
	line[i] = '\0';
	return (line);
}
