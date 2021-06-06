#include "history.h"

static char *set_hist_file(void)
{
	char *home;
	char *user;
	char *hist_path;
	const char *hist_file = "/.crash_history";

	home = getenv("HOME");
	if (NULL == home)
	{
		user = getenv("USER");
		if (user)
			home = ft_strjoin(HOME_DIR, user);
		user = getenv("USERNAME");
		if (!home && user)
			home = ft_strjoin(HOME_DIR, user);
		user = getenv("LOGNAME");
		if (!home && user)
			home = ft_strjoin(HOME_DIR, user);
		else
			return (NULL);
		hist_path = ft_strjoin(home, hist_file);
		free(home);
	}
	else
		hist_path = ft_strjoin(home, hist_file);	
	return (hist_path);
}

static void	read_history_file(t_lsthead *hist_head, char *hist_file)
{
	int		fd;	
	char	*line;
	int		gnl_ret;

	fd = open(hist_file, O_RDONLY | O_CREAT, 0600);
	if (fd == -1)
		return ;
	gnl_ret = get_next_line(fd, &line);
	while (gnl_ret > 0)
	{
		push_list(hist_head, line);
		gnl_ret = get_next_line(fd, &line);
	}
	if (gnl_ret == -1)
		exit_message("Bad access to hist file", EXIT_FAILURE);
	remove_extra_tails(hist_head);
	close(fd);
}

t_hist	*init_history(void)
{
	t_hist		*s_hist;
	
	s_hist = malloc(sizeof(*s_hist));
	if (!s_hist)
		exit_message("Allocation of memory failure", SYS_ERROR);
	*s_hist = (t_hist){0};
	s_hist->hist_file = set_hist_file();
	s_hist->hist_head = malloc(sizeof(*s_hist->hist_head));
	if (NULL == s_hist->hist_head)
		exit_message("Allocation of memory failure", SYS_ERROR);
	*s_hist->hist_head = (t_lsthead){0};
	if (s_hist->hist_file)
		read_history_file(s_hist->hist_head, s_hist->hist_file);
	return (s_hist);
}
