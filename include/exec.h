#ifndef EXEC_H
# define EXEC_H

# include <sys/wait.h>
# include "minishell.h"

/*				exec.c					*/
void		cmdline_exec(t_cmdlst *cmdlst);

/*				pipeline.c				*/
t_cmdlst	*pipe_ctl(t_cmdlst *cmdl);

/*				redirect/out.c			*/
void		redirect_output();	//TODO

/*				rebuild_path.c			*/
void		rebuild_path(void);

/*				path.c					*/
char		*get_path(char *pathname);

/*				getcwd.c				*/
char		*_getcwd(void);

#endif /* EXEC_H */
