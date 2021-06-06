#ifndef READLINE_H
# define READLINE_H

# include "s_terminfo.h"
# include "s_lsthead.h"
# include "s_readline.h"

# include <sys/ioctl.h>

# include "minishell.h"
# include "history.h" 

# define RL_BUFF_SIZE 3

/*
**==================================================================
** PATH: src/readline/readline.c
*/
char	*readline(char *prompt);
char	*rl_internal(size_t prompt_len, t_lsthead *chrlst_head);
void    rl_insert_chr(char chr, t_lsthead *chrlst_head, t_rl_sizes *s);
void    rl_rewrite(t_lsthead *chrlst_head, t_rl_sizes *s);
char	*rl_cat_line(t_lsthead *chrlst_head);

/*
**==================================================================
** PATH: src/readline/cursor.c
*/
bool 				cursor_mov(char *buf, t_lsthead *chr_head, t_rl_sizes *s);
void				mov_right(t_rl_sizes *s);
void				mov_left(t_rl_sizes *s);
void				mov_end(t_rl_sizes *s); 

/*
**==================================================================
** PATH: src/readline/chrlst.c
*/
t_chrlst			*init_chrlst(char chr);
void				free_chrlst(t_chrlst *head);
void				del_chrlst(t_lsthead *head, size_t index);
void				insert_chrlst_node(char chr, t_lsthead *head, size_t index);

/*
**==================================================================
** PATH: src/readline/termios.c
*/
void				termios_init(void);
void				termios_restore(void);
struct s_terminfo	*termcap(void);

/*
**==================================================================
** PATH: src/readline/history.c
*/
bool				history(char *buf, t_lsthead **chrlst_head);

/*
**==================================================================
** PATH: src/readline/clear.c
*/
void				clear_after_cursor(void);

#endif /* READLINE_H */
