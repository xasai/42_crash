#ifndef	S_CMDLST_H 
#define S_CMDLST_H 

typedef struct	s_cmdlst
{
	char			*name;
	char			**arg;
	char			sepch;
	struct s_cmdlst	*next;
	struct s_cmdlst	*prev; // FIXME 
}					t_cmdlst;

#endif /* S_CMDLST_H */
