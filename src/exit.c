#include "minishell.h" 

void	exit_message(char *message, uint8_t code)
{
	if (code == SYS_ERROR && errno)
		print_errno(message);
	else
		putstr_fd(message, STDERR_FILENO);
	exit(code);
}

void	print_errno(char *message)
{
	char	*str_error;

	putstr_fd(message, STDERR_FILENO);
	str_error = strerror(errno);
	putstr_fd(": ", STDERR_FILENO);
	putstr_fd(str_error, STDERR_FILENO);
}
