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

static char *_write_hdoc(char *delim)
{
	int		hdoc_fd;
	char	*filename;
	char	*str;
	size_t	str_len;

	filename = _get_hdoc_filename();
	hdoc_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (-1 == hdoc_fd)
	{
		print_errno("crash");
		putstr_fd("Can't open /tmp directory\n", STDOUT_FILENO);
		free(filename);
		return (NULL);
	}
	str = readline(">");
	while (str)
	{
		DEBUG("STR is \"%s\"\n", str);
		str_len = ft_strlen(str);
		if (!ft_strncmp(delim, str, str_len))
			break ;
		write(hdoc_fd, str, str_len);
		write(hdoc_fd, "\n", 1);
		str = readline(">");
	}
	close(hdoc_fd);
	return (filename);
}

char	*get_hdoc(char *delim)
{
	char	*filename;
	filename = _write_hdoc(delim);
	return (filename);
}
