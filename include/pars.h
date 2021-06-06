#ifndef PARS_H
#define PARS_H
# define EKR_CH			-2  /*253*/
# define DBRCKT_CH		-3	/*252*/
# define OBRCKT_CH		-4	/*251*/
# define SPC_CH			-5	/*250*/
# define BCKSLSH_CH		-6	/*249*/
# define DOLLAR_CH		-7	/*248*/
# define SPACE_SYMB		"\t "

typedef struct	s_dlist
{
	signed char		type; // var, exec
	char			*name;
	char			**arg;
	void			*n_input;
	void			*n_output;
	signed char		sepch;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;

/*
 * 			PARS/
 */
void	brckt_check(t_dlist *l, char *line);
void	separate_analyz(char *word, int name_len, char *sep_len, t_dlist *l);
char	**lineptrjoin(char **ptr, char *line, char free_flag);
char			*substr_ignore(char const *s, unsigned int start, size_t len, const char *sep);
void	specch_replace(t_dlist *l);
void	ft_line_analyz(char *line);
void	line_without_brckt(t_dlist *l, char *line);

#endif
