#include "readline.h"

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
static void	rl_insert_chr(char chr, t_lsthead *chrlst_head, \
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
static char	*rl_cat_line(t_lsthead *chrlst_head)
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

static char	*rl_internal(char *line_buf, t_rl_data *rl)
{
	ssize_t			size;	

	size = 1;
	while (size)
	{
		size = read(STDIN_FILENO, line_buf, RL_BUFF_SIZE);
		line_buf[size] = '\0';
		if (ft_strchr(line_buf, '\n'))
			break ;
		if (cursor_mov(line_buf, rl->chrlst_head, &rl->s))
			continue ;
		else if (history_key(line_buf, rl))
			continue ;
		else if (false) /* FIXME: Check if sig char */
			continue ;
		rl_insert_chr(*line_buf, rl->chrlst_head, &rl->s);
		rl_rewrite(rl->chrlst_head, &rl->s);
	}
	/* free histbuf */
	mov_end(&rl->s);
	return (rl_cat_line(rl->chrlst_head));
}

/*
**==================================================================
** DESCRIOPTION:
**		This fucntion help us to redact our Input in terminal.
**		It allows to us:
**			1) Move across history with up and down arrow keys.
**			2) Move and redact our string in position of cursor.
*/
char	*readline(char *prompt, t_hist *hist)
{
	char			line_buf[RL_BUFF_SIZE + 1];
	char			*line;
	t_lsthead		chrlst_head;
	t_rl_data		rl;
	
	chrlst_head = (t_lsthead){0};
	rl.hist = hist;
	rl.s = (t_rl_sizes){.prompt_len = ft_strlen(prompt), 0};
	rl.chrlst_head = &chrlst_head;
	rl.histbuf = (t_histbuf){.chrlst_head = &chrlst_head, 0};
	ft_bzero(line_buf, RL_BUFF_SIZE + 1);
	termios_init();
	putstr_fd(prompt, STDOUT_FILENO);
	line = rl_internal(line_buf, &rl);
	termios_restore();
	return (line);
}
