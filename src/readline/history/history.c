#include "history.h"

/*
static t_histbuf *new_histbuf(char *line, uint16_t deep, t_rl_sizes s)
{
	t_histbuf *new;
	
	new = malloc(sizeof(*new));
	if (new == NULL)
		exit_message("Memory allocation failure", SYS_ERROR);
	*new = (t_histbuf){.deep = deep};
}
static t_lsthead *hist_up(t_histbuf *histbuf, t_hist *hist)
{
}
static void	hist_down(t_lsthead **chrlst_head, \
					t_histbuf *histbuf, t_hist *hist)
{

}*/

bool	history_key(char *line_buf, t_rl_data *rl)
{
	if (!ft_strncmp(termcap()->k_up, line_buf, 3))
		;
	else if (!ft_strncmp(termcap()->k_down, line_buf, 3))
		;//hist_down();
	else
		return (false);
	(void)rl;
	return (true);
}
