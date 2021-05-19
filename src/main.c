#include "minishell.h"

void handle_args(int ac, char **av)
{
	(void)ac;
	(void)av;
}

int main(int ac, char **av, char **envp)
{
	handle_args(ac, av);
	init_first(ac, av, envp);
	return(interact());
}
