#include "minishell.h" 

void	exit_message(char *message, uint8_t code)
{
	write(2, message, ft_strlen(message)); 
	print_errno();
	exit(code);
}

void	print_errno()
{
	char *str_error;

	if (errno)
	{
		str_error = strerror(errno);
		write(2, ": ", 2);
		write(2, str_error, ft_strlen(str_error));	
	}	
}
