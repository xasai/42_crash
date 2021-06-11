#include "minishell.h"

void print_this_shit(t_dlist *l)
{
	printf("\n");
	while(l->prev)
		l = l->prev;
	printf("\033[1;35m");
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
	printf("\033[1;0m");
}

t_dlist	*add_newl(t_dlist *l)
{
	t_dlist *new_l;

	new_l = malloc(sizeof(t_dlist));
	if (!new_l)
		exit_message("Memory allocation failure", SYS_ERROR);
	*new_l = (t_dlist){0};
	*new_l = (t_dlist){.type = -1, .sepch = -1, .prev = l};
	if (l)
		l->next = new_l;
	return (new_l);
}

t_dlist *ft_line_analyz(char *line)
{
	t_dlist *l;

	l = add_newl(NULL);
	line_without_brckt(l, line);
	return (l);
}

void	ekr_func(char *line, int name_len, char dquot_flag)
{
	line[name_len] = EKR_CH;
	if (dquot_flag)
	{
		if (line[name_len + 1] == '\\')
			line[name_len + 1] = BCKSLSH_CH;
		else if (line[name_len + 1] == '$')
			line[name_len + 1] = DOLLAR_CH;
		else if (line[name_len + 1] == '"')
			;
		else
			line[name_len] = '\\';
	}
	else
	{
		if (line[name_len] == EKR_CH && line[name_len + 1] == '$')
			line[name_len + 1] = DOLLAR_CH;
		else if (line[name_len] == EKR_CH && line[name_len + 1] == ' ')
			line[name_len + 1] = SPC_CH;
		else if (line[name_len] == EKR_CH && line[name_len + 1] == '\\')
			line[name_len + 1] = BCKSLSH_CH;
	}
}

void	flag_change(char *line, int name_len, char *flag, char flag_ch)
{
	line[name_len] = flag_ch;
	if (*flag == 0)
		*flag = 1;
	else
		*flag = 0;
}

void	line_without_brckt(t_dlist *l, char *line)
{
	int		name_len;
	char	dquot_flag;
	char	quot_flag;
	char	sep_len;
	char	sep[] = {DQUOT_CH, QUOT_CH, EKR_CH};

	sep_len = 0;
	quot_flag = 0;
	dquot_flag = 0;
	while(*line)
	{
		name_len = 0;
		while (*line && ft_strchr(SPACE_SYMB, *line))
			++line;
		while ((line[name_len] && (dquot_flag || quot_flag))
				|| !strchr("<>;=| \t", line[name_len]))
		{
			if (!quot_flag && line[name_len] == '\\')
				ekr_func(line, name_len, dquot_flag);
			if (line[name_len] == '\"' && !quot_flag
				&& (!name_len || line[name_len - 1] != EKR_CH))
				flag_change(line, name_len, &dquot_flag, DQUOT_CH);
			else if (line[name_len] == '\'' && !dquot_flag
				&& (!name_len || line[name_len - 1] != EKR_CH))
				flag_change(line, name_len, &quot_flag, QUOT_CH);
			++name_len;
		}
		if (line[name_len] == '=')
			/*work_with_env()*/;
		else
			separate_analyz(line, name_len, &sep_len, l);
		if (!l->name)
		{
			l->name = substr_ignore(line, 0, name_len, sep);// ft_substr(line, 0, name_len);
			l->arg = lineptrjoin(l->arg, substr_ignore(line, 0, name_len, sep), 1);
		}
		else if	(name_len || !l->sepch)
			l->arg = lineptrjoin(l->arg, substr_ignore(line, 0, name_len, sep), 1);
		if (ft_strchr(";><+-|", l->sepch))
			l = add_newl(l);
		line += name_len + sep_len;
	}
	specch_replace(l);
	print_this_shit(l);
}

void	separate_analyz(char *word, int name_len, char *sep_len, t_dlist *l)
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
