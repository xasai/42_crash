#include "readline.h"

/*
** DESCRIOPTION: FIXME FIXME FIXME
**
*/

char *readline(const char *prompt)
{
	char	*line;
	ssize_t size;	
	size_t line_len;
	size_t cursor_pos;

	termios_init();
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));	
	size = 1;
	line_len = 0;
	cursor_pos = 0;
	line = malloc(1000); //FIXME!!!!
	while (size && !ft_strchr(line, '\n'))
	{
		size = read(STDIN_FILENO, line, 100);
		if (cursor_key(line, &line_len, &cursor_pos))
			continue ;
		else if (false) /* Check if control char */
			continue ;	
		write(1, line, size);
		cursor_pos++;
		line_len++;
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_shell->old_termios) < 0)
		exit_message("Could not set interface attributes", 1);
	return (line);
}

bool	history_walking(char *line, size_t *line_len, size_t *cursor_pos)
{
	//VERY RAW function FIXME

	struct s_terminfo *ti;

	(void)cursor_pos;
	(void)line_len;
	ti = &g_shell->terminfo;
	tputs(ti->save_c, 1, &putint);
	if (!ft_strncmp(line, ti->k_up, 3))
	{
		tputs(ti->restore_c, 1, &putint);
		write(1, "PREV\n", 4);
	}
	else if (!ft_strncmp(line, ti->k_down, 3))
	{
		tputs(ti->restore_c, 1, &putint);
		write(1, "NEXT\n", 4);
	}
	else
		return (false);
	return (true);
}
