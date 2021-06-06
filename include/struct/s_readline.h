#ifndef S_READLINE_H
# define S_READLINE_H

# include <stdlib.h>

typedef struct s_chrlst {
	char	 		chr;
	struct s_chrlst *next;
}					t_chrlst;

typedef struct s_rl_sizes
{
	size_t			prompt_len;
	size_t			line_len;
	size_t			cursor_pos;
}					t_rl_sizes;

#endif /* S_READLINE_H */
