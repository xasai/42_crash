#ifndef PARS_H
#define PARS_H

#include <stdbool.h>
#include "struct/s_cmdlst.h"
#include "libft.h"

# define DQUOT_CH	-('\"')
# define QUOT_CH	-('\'')
# define DOLLAR_CH  -('$')

/*			pars.c					*/
t_cmdlst	*ft_line_analyz(char *line);
char        *get_shellarg(char *line, size_t *arg_len);
void		copy_arg(char *line, size_t arg_len, char *buffer);

/*			get_sepch.c					*/
size_t		get_sepch(char *line, t_cmdlst *cmdl);

/*			lineptrjoin.c					*/
char		**lineptrjoin(char **ptr, char *line);

/*			work_with_spase.c					*/
void        skip_spasech(char **line);
size_t      get_spasecount(char *line);

/*			get_qoutcount.c					*/
size_t      get_qoutcount(char *line, size_t arg_len);

/*			get_buffer.c					*/
size_t		get_argbuflen_withquot(char *line, size_t *arg_len);
size_t		get_strbufflen(char *str, size_t *str_len);
void	   	quot_flagchange(char *ch, bool *flag);

/*			heredoc.c					*/
char		*get_hdoc(char *delim);

/*			validate.c					*/
bool		validate_cmd(t_cmdlst *cmdl);

/*			xalloc.c					*/
void        *xalloc(size_t count, size_t size);

/*			redirect_lst.c					*/
t_redir_lst	*append_rlst(t_redir_lst **head, char type);
void		redir_lst_free(t_redir_lst *head);

/*			cmdlst.c						*/
t_cmdlst	*new_cmdlst(t_cmdlst *curr);
void		cmdlst_free(t_cmdlst *cmdlst);

#endif /* PARS_H */
