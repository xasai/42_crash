#include "minishell.h"

void handle_args(int ac, char **av)
{
	if (ac != 1)
		exit(0);
	(void)av;
}

int main(int ac, char **av, char **envp)
{
	handle_args(ac, av);
	init_termios(ac, av, envp);
	readline("crash:");
	return(0);
}
