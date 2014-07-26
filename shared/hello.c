#include <stdio.h>
#include <stdint.h>
uint32_t hello(void* arg)
{
	printf("hello from shared object\n");
	return 0;
}
