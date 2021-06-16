#ifndef BUILTIN_H
# define BUILTIN_H

# define BUILTIN_ERROR 2
# define RETURN_FAILURE 1
# define RETURN_SUCCESS 0

/* 			ENTRY.c			*/
bool builtin_exec(t_dlist *cmd, t_shell *crash);


int	echo_builtin(t_dlist *cmd, t_shell *crash);

int	pwd_builtin(t_dlist *cmd, t_shell *crash);

int	cd_builtin(t_dlist *cmd, t_shell *crash);

int exit_builtin(t_dlist *cmd, t_shell *crash);

int unset_builtin(t_dlist *cmd, t_shell *crash);

int env_builtin(t_dlist *cmd, t_shell *crash);

int export_builtin(t_dlist *cmd, t_shell *crash);


#endif /* BUILTIN_H */
