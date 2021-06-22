#ifndef BUILTIN_H
# define BUILTIN_H

# define BUILTIN_ERROR 2
# define RETURN_FAILURE 1
# define RETURN_SUCCESS 0

/* 			ENTRY.c			*/
bool builtin_exec(t_cmdlst *cmd);


int	echo_builtin(t_cmdlst *cmd);

int	pwd_builtin(t_cmdlst *cmd);

int	cd_builtin(t_cmdlst *cmd);

int exit_builtin(t_cmdlst *cmd);

int unset_builtin(t_cmdlst *cmd);

int env_builtin(t_cmdlst *cmd);

int export_builtin(t_cmdlst *cmd);


#endif /* BUILTIN_H */
