#ifndef __FVM_SHARED_H
#define __FVM_SHARED_H
#include <SDL.h>
typedef struct sVM_api {
	void (*VM_printf)(const char* s, ...);
	SDL_Surface* (*VM_get_surface)(void);
} VM_api_t;
VM_api_t VM_API;
void lib_init(void* vm_printf_ptr, void* vm_get_surface)
{
	VM_API.VM_printf = vm_printf_ptr;
	VM_API.VM_get_surface = vm_get_surface;
}
#endif
