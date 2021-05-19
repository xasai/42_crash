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
		//exit message "Specify terminal type within env variable 'TERM'"
	}
	ret = tgetent(NULL, term_type);
	if (ret < 0)
	{
		;// exit message "Could not access termcap database"
	}
	else if (0 == ret)
	{
		;// exit message "Term type is not defined"
	}
}
