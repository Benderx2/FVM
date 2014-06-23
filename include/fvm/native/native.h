/** native.h - Contains FVM native bridge facilites **/
#ifndef __NATIVE_H
#define __NATIVE_H
#include <stdint.h>
#include <dlfcn.h>
struct FVM_NATIVE_LIB {
	const char* name[64];
	void* handle;
	FVM_NATIVE_LIB* next;
};
typedef struct FVM_NATIVE_LIB NATIVE_LIB_t;
struct FVM_NATIVE_LIST {
	NATIVE_LIB_t* flib;
};
typedef FVM_NATIVE_LIST FVM_NATIVE_LIST_t;
#endif
