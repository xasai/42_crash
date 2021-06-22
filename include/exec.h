#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <sys/wait.h>

/*				exec.c					*/
void	cmdline_exec(t_cmdlst *cmdlst, t_shell *crash);

/*				redirect/out.c		*/
void	redirect_output()

/*				path.c					*/
char	*get_path(char *pathname, char **env_path);
char	*reltoabs(char *rel_path);

/*				rebuild_path.c			*/
void	rebuild_path(t_shell *crash);

/*				getcwd.c				*/
char	*_getcwd(void);

#endif /* EXEC_H */
