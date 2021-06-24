#define SHOW_DEBUG 1
#include <stdio.h>

#define DEBUG(...)\
	if (SHOW_DEBUG)\
	{\
		printf("Debug: %s():%d ", __FUNCTION__, __LINE__);\
		printf(__VA_ARGS__);\
	}
