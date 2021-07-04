#include "minishell.h"

#define SHOW_DEBUG 1

static	char *_get_hdoc_filename(void)
{
	static int		num = 0;
	const char		*part1= "/tmp/hdoc";
	char			*part2;
	char			*filename;
	
	num++;
	if (num < 0)
		num = 0;
	part2 = ft_itoa(num);
	filename = ft_strjoin(part1, part2);
	free(part2);
	if (NULL == filename)
		exit_message("Memory allocation failure", SYS_ERROR);
	return (filename);
}

static char *_read_n_write_hdoc(char *delim, int hdoc_fd, bool expand_env)
{
	char	*str;
	char	*tmp;
	size_t	str_len;

	str = readline(">");
	DEBUG("DELIM is \"%s\"\n", delim);
	while (str)
	{
		if (expand_env)
		{
			tmp = str;
			str = cat_lines_tab((char *[4]){"\"", str, "\"", NULL});
			free(tmp);
			if (!str)
				exit_message("Memory allocation failure", SYS_ERROR);
			tmp = str;
			str = get_shellarg(str, &str_len);
		}
		DEBUG("STR is \"%s\"\n", str);
		str_len = ft_strlen(str);
		if (!ft_strncmp(delim, str, str_len))
			break ;
		write(hdoc_fd, str, str_len);
		write(hdoc_fd, "\n", 1);
		str = readline(">");
	}
	return (NULL);
}

char	*get_hdoc(char *delim)
{	
	int		hdoc_fd;
	char	*filename;
	bool	env_expand;

	filename = _get_hdoc_filename();
	hdoc_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (-1 == hdoc_fd)
	{
		print_errno("crash");
		putstr_fd("Can't open /tmp directory\n", STDOUT_FILENO);
		free(filename);
		return (NULL);
	}
	env_expand = true;//TODO
	_read_n_write_hdoc(delim, hdoc_fd, env_expand);
	close(hdoc_fd);
	return (filename);
}
