#ifndef S_SHELL_H
# define S_SHELL_H

/*	Main struct of crash */
typedef struct s_shell
{
	char	*prompt;
	char	**envp;
	char	**path;
}			t_shell;

#endif /* S_SHELL_H */
