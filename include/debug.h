#include <stdio.h>

#define DEBUG(...)\
	if (SHOW_DEBUG)\
	{\
		printf("\tDEBUG: %s():%d ", __FUNCTION__, __LINE__);\
		printf(__VA_ARGS__);\
	}
