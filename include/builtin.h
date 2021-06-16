#ifndef BUILTIN_H
# define BUILTIN_H

# define RETURN_FAILURE 1
# define RETURN_SUCCESS 0

bool builtin_exec(t_dlist *cmd, t_shell *crash);

int	crash_echo(t_dlist *cmd, t_shell *crash);

int	crash_pwd(t_dlist *cmd, t_shell *crash);

int	crash_cd(t_dlist *cmd, t_shell *crash);

#endif /* BUILTIN_H */
