#include "minishell.h"
//Все индексы нужно поменять на беззнаковый size_t.
//Стоит так делать со всеми переменными которые не должы быть отрицательными

#define SHOW_DEBUG 0

//static
void	flag_change(char *line, int name_len, char *flag, char flag_ch)
{
	line[name_len] = flag_ch;
	if (*flag == 0)
		*flag = 1;
	else
		*flag = 0;
}

//stati
static void wq_fc(char *ch, bool *flag)
{
	*ch *= -1;
	*flag ^= true;// 1 ^ 1 = 0 | 0 ^ 1 = 1
}

//echo qqq$LS"vvv$LS"bbb'$LS'
static void	line_quotvar_hf(char **line, int *name_len, int	*env_falg)
{
	bool	dquot_flag;
	bool	quot_flag;

	dquot_flag = 0;
	quot_flag = 0;
	while (((*line)[*name_len] && (dquot_flag || quot_flag))
		   || !ft_strchr("<>| \t", (*line)[*name_len]))
	{
		if ((*line)[*name_len] == '\"' && !quot_flag)
			wq_fc(&(*line)[*name_len], &dquot_flag);
			//flag_change((*line), *name_len, &dquot_flag, DQUOT_CH);
		else if ((*line)[*name_len] == '\'' && !dquot_flag)
			wq_fc(&(*line)[*name_len], &quot_flag);
			//flag_change((*line), *name_len, &dquot_flag, DQUOT_CH);
		else if ((*line)[*name_len] == '$' && !quot_flag)
		{
			*env_falg += 1;
			expand_env(line, *name_len, *env_falg);
		}
		++*name_len;
	}
}

static void	line_pars(t_cmdlst *l, char *line)
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
		sep_len = get_sepch(&line[name_len], l);
		if (!l->name)
		{	// TODO check malloc return NULL ptr
			l->name = substr_ignore(line, 0, name_len, sep);
			l->arg = lineptrjoin(l->arg, substr_ignore(line, 0, name_len, sep), 1);
		}
		else if	(name_len || !l->sepch)
			l->arg = lineptrjoin(l->arg, substr_ignore(line, 0, name_len, sep), 1);
		if (sep_len)
			l = add_newl(l);
		DEBUG("name_len = %d\n", name_len);
		line += name_len + sep_len;
	}
}

t_cmdlst *ft_line_analyz(char *line)
{
	t_cmdlst *cmdlst;

	cmdlst = add_newl(NULL);
	line_pars(cmdlst, line);
	return (cmdlst);
}
