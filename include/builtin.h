#ifndef BUILTIN_H
# define BUILTIN_H

int builtin_exec(t_dlist *cmd, t_shell *crash);

int	crash_echo(t_dlist *cmd, t_shell *crash);


#endif /* BUILTIN_H */
