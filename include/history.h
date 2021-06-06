#ifndef HISTORY_H
# define HISTORY_H

# include "s_lsthead.h"

# include "minishell.h"

# include <stdlib.h>


# define HISTSIZE 500

# ifdef __linux__
#  define HOME_DIR "/home/"
# endif /* __linux__ */

# ifdef __APPLE__
#  define HOME_DIR "/Users/"
# endif /* __APPLE__ */

/*
**==================================================================
** PATH: src/readline/history.c
*/
bool history(char *buf, t_lsthead **chrlst_head);

/*
**==================================================================
** PATH: src/readline/init.c
*/
t_hist	*init_history(void);

/*
**==================================================================
** PATH: src/readline/hist_list.c
*/
t_histlst	*init_histlst(char *line);
void		push_list(t_lsthead *lsthead, char *str);
void		remove_extra_tails(t_lsthead *lsthead);

#endif /* HISTORY_H */
