#ifndef PARS_H
#define PARS_H
# define DQUOT_CH		-3	/*252*/
# define QUOT_CH		-4	/*251*/
# define SPACE_SYMB		"\t "

typedef struct	s_cmdlst
{
	char			*name;
	char			**arg;
	void			*n_input;
	void			*n_output;
	signed char		sepch;
	struct s_cmdlst	*next;
	struct s_cmdlst	*prev;
}				t_cmdlst;

/*			src/pars/			*/
t_cmdlst *ft_line_analyz(char *line, t_shell *shell);
void	brckt_check(t_cmdlst *l, char *line);
void	separate_analyz(char *word, int name_len, char *sep_len, t_cmdlst *l);
void	print_this_shit(t_cmdlst *l);
char	**lineptrjoin(char **ptr, char *line, char free_flag);
void	specch_replace(t_cmdlst *l);
void	line_pars(t_cmdlst *l, char *line, char **envp);
char	*substr_ignore(char const *s, unsigned int start, \
				size_t len, const char *sep);
char	*strreplace(char *line, int start, int end, char *substr);

#endif
