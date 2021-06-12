#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <sys/wait.h>

/*				EXEC.c					*/
void	cmdline_exec(t_dlist *cmdlst, t_shell *crash);

/*				PATH.c					*/
char	*get_path(char *pathname, char **env_path);
char	*reltoabs(char *rel_path);

/*				IS_EXIST.c				*/
bool	is_exist(char *path_to_file);

#endif /* EXEC_H */
