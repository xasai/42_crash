#ifndef BUILTIN_H
# define BUILTIN_H

# define BUILTIN_ERROR 2
# define RETURN_FAILURE 1
# define RETURN_SUCCESS 0

/* 			ENTRY.c			*/
bool builtin_exec(t_cmdlst *cmd);


uint8_t	echo_builtin(t_cmdlst *cmd);

uint8_t	pwd_builtin(t_cmdlst *cmd);

uint8_t	cd_builtin(t_cmdlst *cmd);

uint8_t exit_builtin(t_cmdlst *cmd);

uint8_t unset_builtin(t_cmdlst *cmd);

uint8_t env_builtin(t_cmdlst *cmd);

uint8_t export_builtin(t_cmdlst *cmd);


#endif /* BUILTIN_H */
