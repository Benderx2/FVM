#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h> /** For dlopen(), dlsym(), and dlerror()s **/
#include <fvm/cpu/cpu.h>
#include <fvm/native/native.h>
#include <fvm/sdl.h> /** Exposing SDL functions **/
native_handle_t* head;
native_handle_t* tail;
int number_of_handles;
uint32_t* get_mem_buf(void);
FVM_REGISTERS_t* get_cpu_regs(void);
FFLAGS_t* get_fflags(void);
void* load_native_library(char* name)
{
	void *handle;
	handle = dlopen(name, RTLD_LAZY);
	if(!handle){	
		printf("FATAL: Unable to load shared objekt: %s", name);
	}	
	
	native_handle_t* newhandle = (native_handle_t*)malloc(sizeof(native_handle_t));
	newhandle->soname = name;
	newhandle->handle = handle;
	newhandle->next = NULL;
	void (*lib_init)(void*, void*, void*, void*, void*);
	*(void**)(&lib_init) = dlsym(handle, "lib_init");
	if(lib_init == NULL)
	{
		printf("WARNING: lib_init not found! Expect SIGSEGV!\n");
	}
	else {
		(*lib_init)(&SDL_scrn_printf, &SDL_get_scrn_buffer, &get_mem_buf, &get_cpu_regs, &get_fflags );
	}
	if(number_of_handles == 0)
	{
		head = newhandle;
		tail = newhandle;
	}
	else {		
		tail->next = newhandle;
		tail = newhandle;
	}
	number_of_handles++;
	return handle;
	
}
void* returnhandle(char* soname)
{
	native_handle_t* current_handle = head;
	for(int i = 0; i <= number_of_handles; i++)
	{	
		if(!strcmp(current_handle->soname, soname)){
			return current_handle->handle;
		}
		else {
			if(current_handle->next == NULL)
			{
				return NULL;
			}
			current_handle = (struct native_handle*)current_handle->next;
		}
	}
	return NULL;
}
uint32_t native_call(char* name, void* handle, void* arg)
{
	// Clear existing errors.
	dlerror();
	uint32_t (*function)(void*);
	*(void**)(&function) = dlsym(handle, name);
	if(function == NULL)
	{
		printf("WARNING: Requested function not found! Name: %s\n", name);
	}
	return (*function)(arg);
}
uint32_t* get_mem_buf(void)
{
	return Memory32;
}
FVM_REGISTERS_t* get_cpu_regs(void)
{
	return CPU_regs;
}
FFLAGS_t* get_fflags(void)
{
	return CPU_Flags;
}
