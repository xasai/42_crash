#include "minishell.h"

void print_this_shit(t_cmdlst *l)
{
	while(l->prev)
		l = l->prev;
	write(1, "\033[1;35m", sizeof("\033[1;35m"));
	while(l) 
	{
		printf("Name \"%s\"\n", l->name);
		if (l->arg)
		{
			for (int i = 0; l->arg[i]; ++i)
				printf("argv[%i] \"%s\"\n", i, l->arg[i]);
		}
		if (l->sepch != '0')
			printf("separator - %c\n", l->sepch);
		l = l->next;
	}
	write(1, "\033[1;0m", sizeof("\033[1;0m"));
}

t_cmdlst	*add_newl(t_cmdlst *l)
{
	t_cmdlst *new_l;

	new_l = malloc(sizeof(t_cmdlst));
	if (!new_l)
		exit_message("Memory allocation failure", SYS_ERROR);
	*new_l = (t_cmdlst){0};
	*new_l = (t_cmdlst){.sepch = -1, .prev = l};
	if (l)
		l->next = new_l;
	return (new_l);
}

t_cmdlst *ft_line_analyz(char *line, t_shell *shell)
{
	t_cmdlst *l;

	l = add_newl(NULL);
	line_pars(l, line, shell->envp);
	return (l);
}

void	flag_change(char *line, int name_len, char *flag, char flag_ch)
{
	line[name_len] = flag_ch;
	if (*flag == 0)
		*flag = 1;
	else
		*flag = 0;
}
int		env_len(char *line)
{
	int var_len;

	var_len = 0;
	if (ft_isalpha(line[var_len]) || line[var_len] == '_')
		++var_len;
	else if (line[var_len] == '?')
		return (1);
	while(ft_isalnum(line[var_len]) || line[var_len] == '_')
		++var_len;
	return (var_len);
}

void	env_past(char **line, int start, int env_flag, char **envp)
{
	int		var_len;
	char	*var_substr;
	char	*var_name;
	char	*free_line;

	free_line = *line;
	var_len = env_len(&(*line)[start + 1]);
	var_name = ft_substr(*line, start + 1, var_len);
	var_substr = crash_getenv(var_name, envp);
	free(var_name);
	*line = strreplace(*line, start, start + var_len, var_substr);
	if (env_flag > 1)
		free(free_line);
}
//echo qqq$LS"vvv$LS"bbb'$LS'
void	line_quotvar_hf(char **line, int *name_len, int	*env_falg, char **envp)
{
	char	dquot_flag;
	char	quot_flag;

	dquot_flag = 0;
	quot_flag = 0;
	while (((*line)[*name_len] && (dquot_flag || quot_flag))
		   || !ft_strchr("<>| \t", (*line)[*name_len]))
	{
		if ((*line)[*name_len] == '\"' && !quot_flag)
			flag_change((*line), *name_len, &dquot_flag, DQUOT_CH);
		else if ((*line)[*name_len] == '\'' && !dquot_flag)
			flag_change((*line), *name_len, &quot_flag, QUOT_CH);
		else if ((*line)[*name_len] == '$' && !quot_flag)
		{
			*env_falg += 1;
			env_past(line, *name_len, *env_falg, envp);
		}
		++*name_len;
	}
}

void	line_pars(t_cmdlst *l, char *line, char **envp)
{
	int			name_len;
	int 		env_flag;
	char		sep_len;
	const char	sep[] = {DQUOT_CH, QUOT_CH};

	sep_len = 0;
	env_flag = 0;
	while(*line)
	{
		name_len = 0;
		while (*line && ft_strchr(SPACE_SYMB, *line))
			++line;
		line_quotvar_hf(&line, &name_len, &env_flag, envp);
		separate_analyz(line, name_len, &sep_len, l);
		if (!l->name)
		{
			l->name = substr_ignore(line, 0, name_len, sep);// FIXME protect allocated memory
			l->arg = lineptrjoin(l->arg, substr_ignore(line, 0, name_len, sep), 1);
		}
		else if	(name_len || !l->sepch)
			l->arg = lineptrjoin(l->arg, substr_ignore(line, 0, name_len, sep), 1);
		if (ft_strchr("><+-|", l->sepch))
			l = add_newl(l);
		line += name_len + sep_len;
	}
}

void	separate_analyz(char *word, int name_len, char *sep_len, t_cmdlst *l)
{
	if (word[name_len] == '>' && word[name_len + 1] == '>')
	{
		l->sepch = '+';
		*sep_len = 2;
	}
	else if (word[name_len] == '<' && word[name_len + 1] == '<')
	{
		l->sepch = '-';
		*sep_len = 2;
	}
	else if (word[name_len] == '\0')
	{
		l->sepch = '0';
		*sep_len = 0;
	}
	else
	{
		l->sepch = word[name_len];
		*sep_len = 1;
	}
}
