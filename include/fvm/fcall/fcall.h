#ifndef __F_CALL_H
#define __F_CALL_H
#include <fvm/cpu/cpu.h>
#define FCALL_WRITE 0
#define FCALL_READ 1
#define FCALL_PUTPIXEL 2
#define  FCALL_PRINTINT 3
#define FCALL_PRINTFLOAT 4
#define FCALL_FOPEN 5
#define FCALL_FCLOSE 6
#define FCALL_FREAD 7
#define FCALL_FWRITE 8
#define FCALL_FSEEK 9
#define F_ERR -1
int fcall(FVM_REG_t callnum, FVM_REG_t r1, FVM_REG_t r0, FVM_REG_t r2, uint8_t* Memory);
extern uint32_t retval;
#endif
