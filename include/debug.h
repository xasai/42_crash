#include <stdio.h>

#define ORANGE_C "\033[33;1m"
#define RESET_C "\033[1;0m"
#define DEBUG(...)\
	if (SHOW_DEBUG)\
	{\
		printf("\t%sDEBUG: %s():%d ", ORANGE_C, __FUNCTION__, __LINE__);\
		printf(__VA_ARGS__);\
		write(1, RESET_C, sizeof(RESET_C));\
	}
