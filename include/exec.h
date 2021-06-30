#ifndef EXEC_H
# define EXEC_H

# include <sys/wait.h>
# include "minishell.h"

/*				exec.c					*/
void		cmdline_exec(t_cmdlst *cmdlst);

/*				pipeline.c				*/
t_cmdlst	*pipe_ctl(t_cmdlst *cmdl);

/*				redirect/ctl.c */
int			redirect_ctl(t_cmdlst *cmdl);

/*				rebuild_path.c			*/
void		rebuild_path(void);

/*				path.c					*/
char		*get_path(char *pathname);

/*				getcwd.c				*/
char		*_getcwd(void);

/*				wait.c					*/
void		_wait(pid_t	pid);

#endif /* EXEC_H */
