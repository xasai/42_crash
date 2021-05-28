#include "minishell.h"


void	line_without_brckt(t_dlist *l, char *line);
void	work_with_word(char *word, t_dlist **l);
void	separate_analyz(char *word, int name_len, char *sep_len, t_dlist *l);


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
	int i;
	char brckt_flag;
	t_dlist l;

	brckt_flag = 0;
	i = 0;
	list_init(&l);
	while(line[i])
		if(strchr("\"'", line[i++]))
		{
			brckt_flag = 1;
			break;
		}
	if (brckt_flag)
		/*line_with_brckt()*/;
	else
		line_without_brckt(&l, line);
}

void	line_without_brckt(t_dlist *l, char *line)
{
	char **str;

	str = splitsep(line," \t"); //more space symbol
	while(*str)
		work_with_word(*str++, &l);
	printf("\n");
	while(l)
	{
		printf("adres - %p | command_name - %s | arg - %s | sep_ch - %c\n",
		 l,
		 l->name,
		 l->arg,
		 l->sepch
		 );
		l = l->prev;
	}
}

void	work_with_word(char *word, t_dlist **l)
{
	int name_len;
	char sep_len;

	name_len = 0;
	while(*word)
	{
		while(word[name_len] && !strchr("<>;=", word[name_len]))
			++name_len;
		if (word[name_len] == '=')
			/*work_with_env()*/;
		else
			separate_analyz(word, name_len, &sep_len, *l);
		if (!(*l)->name)
			(*l)->name = ft_substr(word, 0, name_len);
		else if	(!(*l)->arg)
			(*l)->arg = ft_substr(word, 0, name_len);
		else
			(*l)->arg = strjoin_free((*l)->arg, ft_substr(word, 0, name_len), 1);
		if (ft_strchr(";><+-", (*l)->sepch))
			(*l) = add_newl((*l));
		word += name_len + sep_len;
	}
} //"ls  -a  -l ;ls;echo  eded <   cat >> ls <cat";

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

