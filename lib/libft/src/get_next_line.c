#include "libft.h"

char	*gnl_strdup(char *str, ssize_t size)
{
	char	*new_str;
	int		i;

	i = -1;
	if (!str || size < 0)
		return (NULL);
	new_str = malloc(sizeof(*new_str) * (size + 1));
	if (!new_str)
		return (NULL);
	while (++i <= size)
		new_str[i] = str[i];
	new_str[size] = '\0';
	return (new_str);
}

int	rebuild_remainder(t_rem *remainder, int endl,
									char **line, t_head *lst_head)
{
	char	*tmp;

	*line = gnl_strdup(remainder->string, endl);
	if (*line == NULL)
		return (gnl_clear(lst_head, remainder, line, -1));
	remainder->size -= endl + 1;
	if (remainder->size < 0)
		return (gnl_clear(lst_head, remainder, line, -1));
	tmp = gnl_strdup(&(remainder->string)[endl + 1], remainder->size);
	if (!tmp)
		return (gnl_clear(lst_head, remainder, line, -1));
	gnl_clear(lst_head, NULL, NULL, 0);
	free(remainder->string);
	remainder->string = tmp;
	return (1);
}

int	read_line(int fd, char **line, t_rem *rm, t_head **lst_head)
{
	t_read	r;

	r = (t_read){.endl = -1, .size = 0};
	while (r.endl == -1)
	{
		r.buf = malloc(sizeof(*(r.buf)) * BUFFER_SIZE + 1);
		if (!r.buf)
			return (gnl_clear(*lst_head, rm, line, -1));
		r.size = read(fd, r.buf, BUFFER_SIZE);
		if (r.size <= 0)
			break ;
		r.endl = find_endl(r.buf, r.size);
		if (r.endl != -1)
			gnl_append_buff(lst_head, r.buf, r.endl);
		else if (r.endl == -1)
			gnl_append_buff(lst_head, r.buf, r.size);
	}
	if (r.size <= 0)
		free(r.buf);
	return (read_check(r, line, rm, lst_head));
}	

int	read_check(t_read r, char **line, t_rem *rm, t_head **lst_head)
{
	if (r.size > 0 && r.endl > -1 && ++r.endl < r.size)
	{
		rm->size = r.size - r.endl;
		rm->string = gnl_strdup(&r.buf[r.endl], r.size - r.endl);
		if (NULL == rm->string)
			r.size = -1;
	}
	if ((*lst_head)->overall_size > 0 && r.size != -1)
	{
		*line = gnl_concat(lst_head);
		if (*line)
			return (r.size > 0);
	}
	else if (r.size != -1)
		return (gnl_clear(*lst_head, NULL, line, 0));
	return (gnl_clear(*lst_head, rm, line, -1));
}

int	get_next_line(int fd, char **line)
{
	static t_rem	remainder[OPEN_MAX];
	t_head			*lst_head;
	ssize_t			endl;

	lst_head = malloc(sizeof(*lst_head));
	if (fd < 0 || !line || BUFFER_SIZE <= 0
		|| lst_head == NULL)
		return (-1);
	*lst_head = (t_head){0};
	endl = find_endl(remainder[fd].string, remainder[fd].size);
	if (remainder[fd].string && remainder[fd].size > 0 && endl != -1)
		return (rebuild_remainder(&remainder[fd], endl, line, lst_head));
	else if (remainder[fd].string)
	{
		if (!(gnl_append_buff(&lst_head,
					remainder[fd].string, remainder[fd].size)))
			return (gnl_clear(lst_head, &remainder[fd], line, 0));
		remainder[fd].string = NULL;
	}
	return (read_line(fd, line, &remainder[fd], &lst_head));
}
