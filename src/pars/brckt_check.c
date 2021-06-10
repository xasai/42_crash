#include "minishell.h"

/*void			brckt_check(t_dlist *l, char *line) //not used
{
	int i;
	int brckt_count;
	char oneb_flg;

	i = 0;
	oneb_flg = 0;
	brckt_count = 0;
	while(line[i + 1])
	{
		if(!oneb_flg && line[i] != '\\' && line [i + 1] == '"')
			++brckt_count;
		if(oneb_flg && line[i + 1] == '\'')
		{
			oneb_flg = 0;
			++brckt_count;
		}
		else if(!oneb_flg && line[i] != '\\' && line [i + 1] == '\'')
		{
			oneb_flg = 1;
			++brckt_count;
		}
		++i;
	}
	if (brckt_count % 2 == 1)
	{
		write(STDOUT_FILENO,"BRCKT KO", 8);
		exit(1);//error
	}
	write(STDOUT_FILENO,"BRCKT OK", 8);
}*/

