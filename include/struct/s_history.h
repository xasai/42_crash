#ifndef S_HISTORY_H
# define S_HISTORY_H

# include "s_lsthead.h"

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

typedef struct s_histbuf
{
	t_lsthead			*chrlst_head;
	unsigned short int	deep;
	struct s_histbuf	*next;
	struct s_histbuf	*prev;
}						t_histbuf;

#endif /* S_HISTORY_H */
