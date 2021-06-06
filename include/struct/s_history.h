#ifndef S_HISTORY_H
# define S_HISTORY_H

#include "s_lsthead.h"

typedef struct s_hist
{
	char		*hist_file;
	t_lsthead	*hist_head;
}				t_hist;

typedef struct s_histlst
{
	char				*line;
	struct s_histlst	*next;
	struct s_histlst	*prev;
}						t_histlst;

#endif /* S_HISTORY_H */
