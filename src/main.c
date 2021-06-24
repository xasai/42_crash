#include "minishell.h"

static void	_handle_args(int ac, char **av)
{
	if (ac > 1)
		exit_message("Usage: ./minig_shell", EXIT_FAILURE);
	(void)av;
}

int	main(int ac, char **av, char **envp)
{
	_handle_args(ac, av);
	init_sh(envp);
	return (interact());
}
