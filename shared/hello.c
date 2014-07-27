#include <stdio.h>
#include <stdint.h>
#include "fvm_shared.h"
uint32_t hello(void* arg)
{
	VM_API.VM_printf("hello from shared object\n");
	return 0;
}
