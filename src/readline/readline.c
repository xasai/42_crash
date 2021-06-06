#include "readline.h"

/*
**==================================================================
** DESCRIOPTION:
**		This fucntion help us to redact our Input in terminal.
**		It allows to us:
**			1) Move across history with up and down arrow keys.
**			2) Move and redact our string in position of cursor.
*/
char	*readline(char *prompt)
{
	char			*line;
	t_lsthead		chrlst_head;
	size_t			prompt_len;

	prompt_len = ft_strlen(prompt);
	chrlst_head = (t_lsthead){0};
	termios_init();
	putstr_fd(prompt, STDOUT_FILENO);
	line = rl_internal(prompt_len, &chrlst_head);
	termios_restore();
	return (line);
}

char 	*rl_internal(size_t prompt_len, t_lsthead *chrlst_head)
{
	char			line_buf[RL_BUFF_SIZE + 1];
	ssize_t			size;	
	t_rl_sizes		s;

	size = 1;
	s = (t_rl_sizes){.prompt_len = prompt_len, 0};
	ft_bzero(line_buf, RL_BUFF_SIZE + 1);
	while (size)
	{
		size = read(STDIN_FILENO, line_buf, RL_BUFF_SIZE);
		line_buf[size] = '\0';
		if (ft_strchr(line_buf, '\n'))
			break ;
		if (cursor_mov(line_buf, chrlst_head, &s))
			continue ;
		else if (history(line_buf, &chrlst_head))
			continue ;
		else if (false) /* FIXME: Check if sig char */
			continue ;
		rl_insert_chr(*line_buf, chrlst_head, &s);
		rl_rewrite(chrlst_head, &s);
	}
	mov_end(&s);
	return (rl_cat_line(chrlst_head));
}

/*
**==================================================================
** DESCRIPTION:
**		This function rewrite all after cursor, clear everything after line.
*/
void	rl_rewrite(t_lsthead *chrlst_head, t_rl_sizes *s)
{
	size_t				i;
	t_chrlst			*cur;
	struct winsize		ws;

	i = 0;
	cur = chrlst_head->head;
	if (s->cursor_pos == chrlst_head->size) /* skip if nothing to rewrite */
		return ;
	while (i++ < s->cursor_pos)
		cur = cur->next;
	while (cur)
	{
		putchar_fd(cur->chr, STDOUT_FILENO);
		s->cursor_pos++;
		cur = cur->next;
	}
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) < 0)
		exit_message("Ioctl() function bad return", SYS_ERROR);
	else if (((s->prompt_len + s->cursor_pos + 1) % ws.ws_col) == 1)
		putchar_fd(' ', STDOUT_FILENO);
	clear_after_cursor();
	while (s->cursor_pos >= i)
		mov_left(s);
}

/*
**==================================================================
** DESCRIPTION:
**		This function insert one new node in chr_lst linked list.
**		New node initialized on	heap, and take a place as 
**		cursor_pos index node.
**		Increase cursor_pos by 1.
**		Increase chrlst_head->size by 1.
**		Increase line_len by 1.
**		Assign chrlst_head->head if neccessary.
**	
**		Program exits if initialization of new node failed.
*/
void	rl_insert_chr(char chr, t_lsthead *chrlst_head, \
		t_rl_sizes *s)	
{
	if (chr == '\n')
		return ;
	insert_chrlst_node(chr, chrlst_head, s->cursor_pos);
	write(STDOUT_FILENO, &chr, 1);
	s->line_len++;
	s->cursor_pos++;
}

/*
**==================================================================
** PATH: src/readline/readline.c
**
** DESCRIPTION:
**      Allocate list size * sizeof(char) bytes.
**      Concatenate all lists' chr to string.
**
**  RETURN VALUE
**     	STRING	if concatination succeed 
**      NULL 	if allocation failed.
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
		cur = next;
	}
	line[i] = '\0';
	return (line);
}
