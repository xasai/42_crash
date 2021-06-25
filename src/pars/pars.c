#include "minishell.h"

#define SHOW_DEBUG 0//0 to off | 1 to on debug messages

void print_this_shit(t_cmdlst *l)
{
	while(l->prev)
		l = l->prev;
	write(1, "\033[1;35m", sizeof("\033[1;35m"));
	while(l) 
	{
		printf("\tName \"%s\"\n", l->name);
		if (l->arg)
		{
			for (int i = 0; l->arg[i]; ++i)
				printf("\targv[%i] \"%s\"\n", i, l->arg[i]);
		}
		if (l->sepch)
			printf("\tsepch %c\n", l->sepch);
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
	*new_l = (t_cmdlst){.prev = l};//Такая инициализация занулит все кроме .prev
	// На счет поля prev, под сомнением, оно скорее всего никак не пригождается.
	if (l)
		l->next = new_l;
	return (new_l);
}

t_cmdlst *ft_line_analyz(char *line)
{
	t_cmdlst *cmdlst;

	cmdlst = add_newl(NULL);
	line_pars(cmdlst, line);
	return (cmdlst);
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

void	env_past(char **line, int start, int env_flag)
{
	int		var_len;
	char	*var_substr;
	char	*var_name;
	char	*free_line;

	free_line = *line;
	var_len = env_len(&(*line)[start + 1]);
	var_name = ft_substr(*line, start + 1, var_len);
	var_substr = crash_getenv(var_name);
	free(var_name);
	*line = strreplace(*line, start, start + var_len, var_substr);
	if (env_flag > 1)
		free(free_line);
}

//echo qqq$LS"vvv$LS"bbb'$LS'
void	line_quotvar_hf(char **line, int *name_len, int	*env_falg)
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
			env_past(line, *name_len, *env_falg);
		}
		++*name_len;
	}
}

void	line_pars(t_cmdlst *l, char *line)
{
	int			name_len;
	int 		env_flag;
	size_t		sep_len;
	const char	sep[] = {DQUOT_CH, QUOT_CH};

	env_flag = 0;
	while(*line)
	{
		name_len = 0;
		while (ft_isspace(*line))
			++line;
		line_quotvar_hf(&line, &name_len, &env_flag);
		sep_len = separate_analyz(&line[name_len], l);
		if (!l->name)
		{	// TODO check malloc return NULL ptr
			l->name = substr_ignore(line, 0, name_len, sep);
			l->arg = lineptrjoin(l->arg, substr_ignore(line, 0, name_len, sep), 1);
		}
		else if	(name_len || !l->sepch)
			l->arg = lineptrjoin(l->arg, substr_ignore(line, 0, name_len, sep), 1);
		if (sep_len)//Память под sep_len лежит ближе чем под l->sepch
			l = add_newl(l);
		DEBUG("name_len = %d\n", name_len);
		line += name_len + sep_len;
	}
}


// TODO TEST (обычные тесты проходит)
// Бывшая separate_analyze()
// Сейчас онa принимает только два аргумента,
// устанавливает cmdl->sepch только на < > + - | , и остается неинициализированной 
// если подходящего сепаратора в line нет .
// Возвращает длину сепараторa, чтобы в дальнейшем пройти по строке вперед
size_t	get_sepch(char *line, t_cmdlst *cmdl)
{
	size_t	len;

	len = 0;
	if (line[0] == line[1] && (line[0] == '>' || line[0] == '<'))
	{
		if (line[1] == '>')
			cmdl->sepch = '+';
		else if (line[1] == '<')
			cmdl->sepch = '-';
		len = 2;
	}
	else if (line[0] == '|' || line[0] == '>' || line[0] == '<')
	{
		cmdl->sepch = line[0];
		len = 1;
	}
	DEBUG("Sepch is: \"%c\"\n", cmdl->sepch);
	return (len);
}
