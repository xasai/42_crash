#ifndef EXEC_H
# define EXEC_H

# include <sys/wait.h>
# include "minishell.h"

/*				exec.c					*/
void	cmdline_exec(t_cmdlst *cmdlst);

/*				redirect/out.c		*/
void	redirect_output();	//TODO

/*				path.c					*/
char	*get_path(char *pathname, char **env_path);
char	*reltoabs(char *rel_path);

/*				rebuild_path.c			*/
void	rebuild_path(void);

/*				getcwd.c				*/
char	*_getcwd(void);

#endif /* EXEC_H */
