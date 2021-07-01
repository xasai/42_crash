#ifndef S_REDIR_LST_H
# define S_REDIR_LST_H

typedef struct s_redir_lst
{
	char				type;
	char				*filename;
	struct s_redir_lst	*next;
}						t_redir_lst;

#endif /* S_REDIR_LST_H */
