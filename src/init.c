#include "minishell.h"

void	init_first(int ac, char **av)
{
	(void)ac;
	(void)av;
	term_capability_data_init();
}

void	term_capability_data_init(void)
{
	char		*term_type;
	int			ret;

	term_type = getenv("TERM");
	if (0 == term_type)
	{
		exit_message("Specify terminal type within env variable 'TERM'", 1);
	}
	ret = tgetent(NULL, term_type);
	if (ret < 0)
	{
		exit_message("Could not access termcap database", 1);
	}
	else if (0 == ret)
	{
		exit_message("Your terminal type is not defined", 1);
	}
}
