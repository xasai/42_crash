#include "minishell.h"

#include <stdio.h>

void handle_args(int ac, char **av)
{
	(void)ac;
	(void)av;
	printf("asdfasdfA");
}

int main(int ac, char **av)
{
	handle_args(ac, av);
	init_first(ac, av);
}
