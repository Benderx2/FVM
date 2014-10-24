/** native.h - Contains FVM native bridge facilites **/
#ifndef __NATIVE_H
#define __NATIVE_H
#include <stdint.h>
#include <dlfcn.h>
typedef struct native_handle {
	char* soname;
	void* handle;
	struct native_handle* next;
} native_handle_t;
void* load_native_library(char* name);
uint32_t native_call(char* name, void* handle, void* arg);
void* returnhandle(char* soname);
#endif
