#ifndef S_LSTHEAD_H
# define S_LSTHEAD_H

#include <stdlib.h>

typedef struct s_lsthead
{
	void		*head;
	void		*tail;
	size_t		size;
}				t_lsthead;

#endif /* S_LSTHEAD_H */
