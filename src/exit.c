#include "minishell.h" 

void	exit_message(char *message, uint8_t code)
{
	print_errno(message);
	exit(code);
}

void	print_errno(char *message)
{
	char *str_error;

	putstr_fd(message, STDERR_FILENO);	
	if (errno)
	{
		str_error = strerror(errno);
		putstr_fd(": ", STDERR_FILENO);
		putstr_fd(str_error, STDERR_FILENO);	
	}	
	putchar_fd('\n', STDERR_FILENO);
}
