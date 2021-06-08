#ifndef S_READLINE_H
# define S_READLINE_H

# include <stdlib.h>
# include "s_lsthead.h"
# include "s_history.h"

typedef struct s_chrlst {
	char	 		chr;
	struct s_chrlst *next;
}					t_chrlst;

typedef struct s_rl_sizes
{
	size_t			prompt_len;
	size_t			line_len;
	size_t			cursor_pos;
}					t_rl_sizes;

typedef struct	s_rl_data
{
	t_rl_sizes	s;	
	t_lsthead	*chrlst_head;
	t_histbuf	histbuf;
	t_hist		*hist;
}				t_rl_data;

#endif /* S_READLINE_H */
