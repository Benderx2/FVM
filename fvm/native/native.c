#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h> /** For dlopen(), dlsym(), and dlerror()s **/
#include <fvm/native/native.h>
native_handle_t* head;
native_handle_t* tail;
int number_of_handles;
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
	if(number_of_handles == 0)
	{
		head = newhandle;
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
			i++;
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
	return (*function)(arg);
}
