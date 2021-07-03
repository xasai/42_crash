#ifndef EXEC_H
# define EXEC_H

//PATH:	execute/

/*			exec.c					*/
void		cmdline_exec(t_cmdlst *cmdlst);

/*			pipeline.c				*/
t_cmdlst	*pipe_ctl(t_cmdlst *cmdl);

/*			redirect.c				*/
bool		redirect_ctl(t_cmdlst *cmdl);

/*			path.c					*/
char		*get_path(char *pathname);

/*			rebuild_path.c			*/
void		rebuild_path(void);

/*			wrappers/wrappers.c		*/
void		_wait(int pid);
char		*_getcwd(void);

#endif /* EXEC_H */
