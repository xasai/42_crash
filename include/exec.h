#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include "pars.h"

# include "struct/s_shell.h"

void	cmdline_exec(t_dlist *cmdlst, t_shell *crash);

#endif /* EXEC_H */
