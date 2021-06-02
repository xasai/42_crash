#include "minishell.h"





void print_thit_shit(t_dlist *l)
{
	printf("\n");
	while(l->prev)
		l = l->prev;
	while(l) {
		printf("adres - %p | command_name - %s | argument - ",
			   l,
			   l->name
		);
		if (l->arg)
			for (int i = 0; l->arg[i]; ++i)
				printf("%i) %s ", i, l->arg[i]);
		else
			printf("null ");
		printf("| sepch - %c\n", l->sepch);
		l = l->next;
	}
}


void	list_init(t_dlist *l)
{
	l->type		= -1; // var, bin
	l->name		= NULL;
	l->arg		= NULL;
	l->n_input	= NULL;
	l->n_output	= NULL;
	l->sepch	= -1;
	l->next		= NULL;
	l->prev		= NULL;
}

t_dlist	*add_newl(t_dlist *l)
{
	t_dlist *new_l;

	new_l = malloc(sizeof(t_dlist));
	list_init(new_l);
	l->next = new_l;
	new_l->prev = l;
	return (new_l);
}

void	ft_line_analyz(char *line)
{
	t_dlist l;

	list_init(&l);
	line_without_brckt(&l, line);
}

void	line_without_brckt(t_dlist *l, char *line)
{
	int		name_len;
	char	dbrckt_flag;
	char	obrckt_flag;
	char	sep_len;

	sep_len = 0;
	obrckt_flag = 0;
	dbrckt_flag = 0;
	while(*line)
	{
		name_len = 0;
		while (*line && strchr(SPACE_SYMB, *line))
			++line;
		while ((line[name_len] && (dbrckt_flag || obrckt_flag))
				|| !strchr("<>;=| \t", line[name_len]))
		{
			if (!obrckt_flag  && !dbrckt_flag)
			{
				if (line[name_len] == '\\')
					line[name_len] = EKR_CH;
				if (line[name_len] == EKR_CH && line[name_len + 1] == '\\')
					line[name_len + 1] = BCKSLSH_CH;
				else if (line[name_len] == EKR_CH && line[name_len + 1] == '"')
					line[name_len + 1] = DBRCKT_CH;
				else if (line[name_len] == EKR_CH && line[name_len + 1] == '\'')
					line[name_len + 1] = OBRCKT_CH;
				else if ((line[name_len] == EKR_CH && ft_strchr(SPACE_SYMB, line[name_len + 1])))
					line[name_len + 1] = SPC_CH;
			}
			if (line[name_len] == '"' && !obrckt_flag)
			{
				if (dbrckt_flag == 0)
					dbrckt_flag = 1;
				else
					dbrckt_flag = 0;
			}
			else if (line[name_len] == '\'')
			{
				if (obrckt_flag == 0)
					obrckt_flag= 1;
				else
					obrckt_flag = 0;
			}
			++name_len;
		}
		if (line[name_len] == '=')
			/*work_with_env()*/;
		else
			separate_analyz(line, name_len, &sep_len, l);
		if (!l->name)
			l->name = substr_ignore(line, 0, name_len, EKR_CH);// ft_substr(line, 0, name_len);
		else if	(name_len || !l->sepch)
			l->arg = lineptrjoin(l->arg, substr_ignore(line, 0, name_len, EKR_CH), 1);
		if (ft_strchr(";><+-|", l->sepch))
			l = add_newl(l);
		line += name_len + sep_len;
	}
	/*specch_replace(l);*/
	print_thit_shit(l);
	exit(0);
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
	else if (word[name_len] == 0)
	{
		l->sepch = '0';
		*sep_len = 0;
	}
	else
	{
		l->sepch = word[name_len];
		*sep_len = 1;
	}
	l->type = 'e';
}
