#ifndef S_CMDLST_H
# define S_CMDLST_H

# include "s_redir_lst.h"

typedef struct s_cmdlst
{
	char			*pathname;
	char			**args;
	char			sepch;
	t_redir_lst		*rlst;
	struct s_cmdlst	*next;
	struct s_cmdlst	*prev;
}					t_cmdlst;

#endif /* S_CMDLST_H */
