#include "minishell.h"

/*
 *  you can send only a dynamically allocated line
 */
char **lineptrjoin(char **ptr, char *line, bool free_flag)
{
	//Можно сделать эту функцию универсальнее
	//И применимой к любому типу указателей
	char	**new_ptr;
	int		ptr_len;

	ptr_len = 0;
	if (ptr)
		while(ptr[ptr_len])
			++ptr_len;
	// Если ptr = NULL аллоцируется 2 указателя сразу
	new_ptr = malloc(sizeof(char *) * (ptr_len + 2));
	if (!new_ptr)
		return (NULL);
	new_ptr[ptr_len + 1] = NULL;
	new_ptr[ptr_len] = line;

 	//бессмысленная проверка на ptr, ptr_len == 0, если !ptr
	while(ptr && --ptr_len >= 0)
		new_ptr[ptr_len] = ptr[ptr_len];

	//скорее всего это функция будет использоваться часто
	//с флагом на единичку.
	if (free_flag == true)
		free(ptr);
	return (new_ptr);
}
