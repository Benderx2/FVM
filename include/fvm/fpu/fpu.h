#ifndef __FPU_H
#define __FPU_H
#include <stdint.h>
struct FVM_FPU {
	uint32_t flags[5]; /** 5 Flags for the FPU **/
	uint32_t stack; /** FPU Stack **/
};
typedef struct FVM_FPU FVM_FPU_t;
#endif

