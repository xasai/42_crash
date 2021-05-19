#include "minishell.h" 

void	exit_message(char *message, uint8_t code)
{
	if (errno)
		perror(message);
	else 
		write(2, message, ft_strlen(message)); 
	exit(code);
}
