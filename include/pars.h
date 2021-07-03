#ifndef PARS_H
#define PARS_H

#include <stdbool.h>
#include "struct/s_cmdlst.h"
#include "libft.h"

# define DQUOT_CH	-('\"')
# define QUOT_CH	-('\'')
# define DOLLAR_CH  -('$')


t_cmdlst	*ft_line_analyz(char *line);



t_cmdlst	*add_newl(t_cmdlst *curr);

void		expand_env(char **line, int start, int env_flag);

size_t		get_sepch(char *line, t_cmdlst *cmdl);

char		**lineptrjoin(char **ptr, char *line);

char		*substr_ignore(char const *s, unsigned int start_idx, \
						size_t len, const char *sep);

char		*strreplace(char *line, int start, int end, char *substr);


void		print_this_shit(t_cmdlst *l); //FIXME

size_t      sstrlen(char *s, char *ignored, size_t start, size_t end);

void        skip_spasech(char **line);


t_redir_lst	*append_rlst(t_redir_lst **head, char type);
char		*get_shellarg(char **line, size_t *arg_len);

#endif /* PARS_H */
