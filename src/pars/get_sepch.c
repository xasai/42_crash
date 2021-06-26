#include "minishell.h"

#define SHOW_DEBUG 0
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
