#ifndef __FVM_ERR_H
#define __FVM_ERR_H
#include <stdint.h>
#define FVM_NO_ARG_ERR -1
#define FVM_NO_MEM -2
#define FVM_NO_ROM -3
#define FVM_LARGE_ROM -4
#define FVM_FATAL_ERR -5
#define FVM_PROGRAM_ERR -6
#define FVM_NO_ERR 0
void FVM_EXIT(int ERR_CODE);
#endif
