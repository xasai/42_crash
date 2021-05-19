#include "libft.h"

void	*gnl_append_buff(t_head **head, char *str, ssize_t size)
{
	t_gnl	*new;

	new = malloc(sizeof(*new));
	if (NULL == new)
		return (NULL);
	str[size] = '\0';
	new->next = NULL;
	new->string = str;
	new->size = size;
	if (!(*head)->overall_size)
	{
		(*head)->head = new;
		(*head)->tail = new;
		(*head)->overall_size = size + 1;
	}
	else
	{
		(*head)->tail->next = new;
		(*head)->tail = new;
		(*head)->overall_size += size;
	}
	return (*head);
}

char	*gnl_concat(t_head **head)
{
	int		all_size;
	t_gnl	*list;
	char	*str;
	int		i;
	int		k;

	all_size = (*head)->overall_size;
	str = malloc(sizeof(*str) * all_size);
	if (NULL == str || 0 == all_size)
		return (NULL);
	list = (*head)->head;
	k = 0;
	while (list && all_size)
	{
		i = 0;
		while (i < list->size)
		{
			str[k++] = (list->string)[i++];
			all_size--;
		}
		list = list->next;
	}
	str[(*head)->overall_size - 1] = '\0';
	gnl_clear(*head, NULL, NULL, 0);
	return (str);
}

int	gnl_clear(t_head *head, t_rem *remainder, char **line, int ret)
{
	t_gnl	*tmp;
	t_gnl	*list;

	if (remainder)
	{
		free(remainder->string);
		*remainder = (t_rem){NULL, 0};
	}
	if (head)
	{
		list = head->head;
		while (list)
		{
			tmp = list;
			list = list->next;
			free(tmp->string);
			free(tmp);
		}
		*head = (t_head){NULL, NULL, 0};
		free(head);
		head = NULL;
	}
	if (line)
		*line = gnl_strdup("", 0);
	return (ret);
}

int	find_endl(char *str, ssize_t size)
{
	int	i;

	i = -1;
	if (!str)
		return (-1);
	while (++i < size && str[i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}
