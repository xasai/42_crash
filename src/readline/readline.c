#include "minishell.h"


void readline(const char *prompt)
{
	char	*line = ft_strdup("ls \\\" \\ \"fefef ' ef e' \" \\\" -a  -l ; ;ls;echo  eded <   cat >> ls <cat");
	// "ls \\\" \\ \"fefef ' ef e' \" \\\" -a  -l ; ;ls;echo  eded <   cat >> ls <cat"
	// "\\ "
	// "ls  -a  -l ; ;ls;echo  eded <   cat >> ls <cat";
	int	gnl_ret;

	gnl_ret = 1;
	while (gnl_ret)
	{
		write(1, prompt, ft_strlen(prompt));
//		gnl_ret = get_next_line(STDIN_FILENO, &line);
		ft_line_analyz(line);
	}
	if (gnl_ret == -1)
	{
		free(line);
		exit_message("In function readline() ", 1);
	}
}
