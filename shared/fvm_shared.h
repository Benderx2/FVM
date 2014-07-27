#ifndef __FVM_SHARED_H
#define __FVM_SHARED_H
typedef struct sVM_api {
	void (*VM_printf)(const char* s, ...);
} VM_api_t;
VM_api_t VM_API;
void lib_init(void* vm_printf_ptr)
{
	VM_API.VM_printf = vm_printf_ptr;
}
#endif
