#ifndef __F_CALL_H
#define __F_CALL_H
#include <fvm/cpu/cpu.h>
#define FCALL_WRITE 0
#define F_ERR -1
int fcall(FVM_REG_t r0, FVM_REG_t r1);
#endif
