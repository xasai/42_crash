#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "s_terminfo.h"

# include <unistd.h>
# include <fcntl.h>
# include <termcap.h> 
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

# include <stdint.h>
# include <limits.h>
# define EKR_CH -3
# define DBRCKT_CH -4
# define OBRCKT_CH -5
# define SPC_CH -6
# define BCKSLSH_CH -7
# define SPACE_SYMB "\t "
extern t_terminfo *g_term;



typedef struct	s_dlist
{
	signed char		type; // var, bin
	char			*name;
	char			**arg;
	void			*n_input;
	void			*n_output;
	signed char		sepch;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;


/*
**			MAIN.c
*/
void			handle_args(int ac, char **av);

/*
** 			INIT.c
*/
void			init_termios(int ac, char **av, char **envp);
void			term_capability_data_init(void);
struct termios	termios_init(void);

/*
**			EXIT.c
*/
void			exit_message(char *message, uint8_t code);
void			print_errno(void);

/*
**		 	READLINE/READLINE.c
*/
int				interact(void);
void			readline(const char *prompt);


/*
 * 			PARS/
 */
void	brckt_check(t_dlist *l, char *line);
void	separate_analyz(char *word, int name_len, char *sep_len, t_dlist *l);
char	**lineptrjoin(char **ptr, char *line, char free_flag);
char	*substr_ignore(char const *s, unsigned int start, size_t len, char c);
void	specch_replace(t_dlist *l);
void	ft_line_analyz(char *line);
void	line_without_brckt(t_dlist *l, char *line);

#endif
