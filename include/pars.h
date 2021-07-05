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

size_t      get_spasecount(char *line);

char        *get_shellarg(char *line, size_t *arg_len);

size_t      get_strbufflen(char *str, size_t *str_len);

size_t      get_qoutcount(char *line, size_t arg_len);

size_t      get_envkey_len(char *line);

size_t      get_envvalue_len(char *line, size_t envkey_len);

void	   	quot_flagchange(char *ch, bool *flag);

void        copy_arg(char *line, size_t arg_len, char *buffer);

void        print_this_shit(t_cmdlst *l);

char		*get_hdoc(char *delim);

bool		validate_cmd(t_cmdlst *cmdl);

void        *xalloc(size_t count, size_t size);

/*			redirect_lst.c					*/
t_redir_lst	*append_rlst(t_redir_lst **head, char type);

void		redir_lst_free(t_redir_lst *head);

/*			cmdlst.c						*/
t_cmdlst	*new_cmdlst(t_cmdlst *curr);

void		cmdlst_free(t_cmdlst *cmdlst);

#endif /* PARS_H */
