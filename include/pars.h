#ifndef PARS_H
#define PARS_H

//# define DQUOT_CH	-3 
//# define QUOT_CH	-4
# define DQUOT_CH	-('\"')
# define QUOT_CH	-('\'')

t_cmdlst	*ft_line_analyz(char *line);

t_cmdlst	*add_newl(t_cmdlst *curr);

void		expand_env(char **line, int start, int env_flag);

size_t		get_sepch(char *line, t_cmdlst *cmdl);

char		**lineptrjoin(char **ptr, char *line, bool free_flag);

char		*substr_ignore(char const *s, unsigned int start, \
						size_t len, const char *sep);

char		*strreplace(char *line, int start, int end, char *substr);

////////////////////////////////////////////////////////////////////////
void		print_this_shit(t_cmdlst *l);

#endif /* PARS_H */
