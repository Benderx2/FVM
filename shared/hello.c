#include <stdio.h>
#include <stdint.h>
#include "fvm_shared.h"
VM_api_t VM_API;
void lib_init(void* vm_printf_ptr)
{
	VM_API.VM_printf = vm_printf_ptr;
}
uint32_t hello(void* arg)
{
	VM_API.VM_printf("hello from shared object\n");
	return 0;
}
