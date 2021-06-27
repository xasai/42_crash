#ifndef S_REDIRECT_LST_H
#define S_REDIRECT_LST_H

typedef struct s_redirect_lst
{
	char		id_ch; // > + - <
	char		*word; // все что послеФ
	struct s_redirect_lst *next; // следующий редирект
}			t_redirect_lst;
#endif /* S_REDIRECT_LST_H */

