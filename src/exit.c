#include "minishell.h" 

void	exit_message(char *message, uint8_t code)
{
	
	putstr_fd(message, STDERR_FILENO);	
	if (code == SYS_ERROR)	
		print_errno();
	putchar_fd('\n', STDERR_FILENO);
	exit(code);
}

void	print_errno(void)
{
	char *str_error;

	if (errno)
	{
		str_error = strerror(errno);
		putstr_fd(": ", STDERR_FILENO);
		putstr_fd(str_error, STDERR_FILENO);	
	}	
}
