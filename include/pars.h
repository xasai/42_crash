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

size_t		get_sepch(char *line, t_cmdlst *cmdl);

char		**lineptrjoin(char **ptr, char *line);

void        skip_spasech(char **line);

t_redir_lst	*append_rlst(t_redir_lst **head, char type);

char        *get_shellarg(char *line, size_t *arg_len);

size_t      get_qoutcount(char *line, size_t arg_len);

size_t      get_envkey_len(char *line);

void    wq_fc(char *ch, bool *flag);

#endif /* PARS_H */
