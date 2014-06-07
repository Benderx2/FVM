#ifndef __GPU_H
#define __GPU_H
#include <float.h>
#include <stdint.h>
struct GPU_REGS
{
	// GPU Registers 5 of them
	float R0;
	float R1;
	float R2;
	float R3;
	float R4;
	float R5;
	uint32_t R6;
	uint32_t R7;
	uint32_t R8;
}
typedef struct GPU_REGS GPU_REGS_t;
int gpu_emulate_instruction(GPU_REGS_t* GPU_REGS, FVM_MEM_t* FVM_MEM, FVM_REGISTERS_t* CPU_REGS);
#endif
