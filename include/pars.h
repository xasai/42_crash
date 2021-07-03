#ifndef PARS_H
#define PARS_H

#include <stdbool.h>
#include "struct/s_cmdlst.h"
#include "libft.h"

# define DQUOT_CH	-('\"')
# define QUOT_CH	-('\'')
# define DOLLAR_CH  -('$')


t_cmdlst	*ft_line_analyz(char *line);


size_t		get_sepch(char *line, t_cmdlst *cmdl);

char		**lineptrjoin(char **ptr, char *line);

void        skip_spasech(char **line);


char        *get_shellarg(char *line, size_t *arg_len);

size_t      get_qoutcount(char *line, size_t arg_len);

size_t      get_envkey_len(char *line);


void	   	quot_flagchange(char *ch, bool *flag);

char		*get_hdoc(char *delim);

t_redir_lst	*append_rlst(t_redir_lst **head, char type);
t_cmdlst	*new_cmdlst(t_cmdlst *curr);
void		cmdlst_free(t_cmdlst *cmdlst);

#endif /* PARS_H */
