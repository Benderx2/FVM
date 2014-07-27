#ifndef __FVM_SHARED_H
#define __FVM_SHARED_H
typedef struct sVM_api {
	void (*VM_printf)(const char* s, ...);
} VM_api_t;
#endif
