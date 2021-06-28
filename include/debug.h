#include <stdio.h>

#define ORANGE_C "\033[33;1m"
#define RESET_C "\033[1;0m"
#define DEBUG(...)\
	if (SHOW_DEBUG)\
	{\
		fprintf(stderr,"\t%sDEBUG: %s():%d ", ORANGE_C, __FUNCTION__, __LINE__);\
		fprintf(stderr,__VA_ARGS__);\
		fprintf(stderr, RESET_C);\
	}
