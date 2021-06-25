#ifndef PARS_H
#define PARS_H
# define DQUOT_CH		-3	/*252*/
# define QUOT_CH		-4	/*251*/
# define SPACE_SYMB		"\t "

typedef struct	s_cmdlst
{
	char			*name;
	char			**arg;
	char			sepch;
	struct s_cmdlst	*next;
	struct s_cmdlst	*prev; // FIXME Check if need 
}				t_cmdlst;

/*			src/pars/			*/
t_cmdlst *ft_line_analyz(char *line);

void	brckt_check(t_cmdlst *l, char *line);

size_t	separate_analyz(char *line, t_cmdlst *cmdl);// TODO
size_t	get_sepch(char *line, t_cmdlst *cmdl);// TODO

void	print_this_shit(t_cmdlst *l);

char	**lineptrjoin(char **ptr, char *line, char free_flag);

void	specch_replace(t_cmdlst *l);

void	line_pars(t_cmdlst *l, char *line);

char	*substr_ignore(char const *s, unsigned int start, \
				size_t len, const char *sep);

char	*strreplace(char *line, int start, int end, char *substr);

#endif
