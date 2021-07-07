#include "minishell.h"

#define SHOW_DEBUG 0

static char	*_get_hdoc_filename(void)
{
	char		*part2;
	char		*filename;
	static int	num = 0;
	const char	*part1 = "/tmp/hdoc";

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

static char	*_hdoc_expand_str(char *str)
{
	size_t	i;
	size_t	buf_len;
	char	*buffer;

	i = 0;
	buf_len = get_strbufflen(str, &i);
	DEBUG("BUF_LEN %lu\n", buf_len);
	buffer = xalloc(buf_len + 1, sizeof(char));
	copy_arg(str, i, buffer);
	free(str);
	return (buffer);
}

static void	_read_n_write_hdoc(char *delim, int hdoc_fd)
{
	char	*str;

	DEBUG("DELIM is \"%s\"\n", delim);
	if (!ft_strlen(delim))
		return ;
	str = readline(">");
	while (str)
	{
		DEBUG("STR is \"%s\"\n", str);
		if (!ft_strcmp(delim, str))
		{
			free(str);
			return ;
		}
		str = _hdoc_expand_str(str);
		putendl_fd(str, hdoc_fd);
		free(str);
		str = readline(">");
	}
	printf("crash: warning: here-document"
		   " delimited by end-of-file (wanted `%s')\n", delim);
}

char	*get_hdoc(char *delim)
{
	int		hdoc_fd;
	char	*filename;

	signal(SIGINT, SIG_IGN);
	if (!ft_strlen(delim))
		return (NULL);
	filename = _get_hdoc_filename();
	hdoc_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (-1 == hdoc_fd)
	{
		print_errno("crash");
		free(filename);
		free(delim);
		return (NULL);
	}
	_read_n_write_hdoc(delim, hdoc_fd);
	close(hdoc_fd);
	free(delim);
	return (filename);
}
