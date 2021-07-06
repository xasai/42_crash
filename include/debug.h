#ifndef DEBUG_H
# define DEBUG_H
#include <stdio.h>

#define ORANGE "\033[33;1m"
#define GREEN "\033[32;1m"
#define RED	"\033[31;1m"
#define RESET "\033[1;0m"

#define DEBUG(...)\
	if (SHOW_DEBUG)\
	{\
		fprintf(stderr,"%sDEBUG: %s():%d ", ORANGE, __FUNCTION__, __LINE__);\
		fprintf(stderr,__VA_ARGS__);\
		fprintf(stderr, RESET);\
	}

#define DEBUG_CMDL(x)\
{\
	if (SHOW_DEBUG && x)\
	{\
		size_t	i;\
		t_cmdlst *l = x;\
		t_redir_lst *rlst;\
		fprintf(stderr,"%s\tDEBUG:\n", GREEN);\
		while(l)\
		{\
			i = 0;\
			fprintf(stderr, "execve(\"%s\", [", l->pathname);\
			if (l->args)\
				while (l->args[i])\
				{\
					if (i)\
						fprintf(stderr, ", ");\
					fprintf(stderr, "\"%s\"", l->args[i++]);\
				}\
			fprintf(stderr, "], **envp)");\
			rlst = l->rlst;\
			while (rlst)\
			{\
				fprintf(stderr, " %c ", rlst->type);\
				if (rlst->filename)\
					fprintf(stderr, "'%s'", rlst->filename);\
				rlst = rlst->next;\
			}\
			fprintf(stderr, "\n");\
			if (l->sepch == '|')\
				fprintf(stderr, "%sPIPE %s", RED, GREEN);\
			l = l->next;\
		}\
		fprintf(stderr,"Exit_status: %d%s\n", g_sh->exit_status, RESET);\
	}\
}
#endif /* DEBUG_H */
