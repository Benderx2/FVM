#ifndef __FVM_SHARED_H
#define __FVM_SHARED_H
#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>
typedef uint32_t FVM_REG_t;
struct FVM_REGISTERS {
	/* GPRs R0 - R10 */
	FVM_REG_t r0;
	FVM_REG_t r1;
	FVM_REG_t r2;
	FVM_REG_t r3;
	FVM_REG_t r4;
	FVM_REG_t r5;
	FVM_REG_t r6;
	FVM_REG_t r7;
	FVM_REG_t r8;
	FVM_REG_t r9;
	FVM_REG_t r10;
	/* Instruction Pointer */
	FVM_REG_t IP;
	/* Stack Pointer */	
	FVM_REG_t r12;
	/* Base Pointer */
	FVM_REG_t r13;
	/* CPU Register */
	FVM_REG_t r14;
	/* Hardware status register */
	FVM_REG_t r15;
	/* Fault registereax */
	FVM_REG_t r16;
	/* CPU2 Register */
	FVM_REG_t r17;
	/* IRET Register */
	FVM_REG_t r18;
	/* ON Register */
	FVM_REG_t ON;
};
struct FFLAGS 
{
	/* Equal Flag */
	uint32_t E;
	/* Zero Flag */
	uint32_t Z;
	/* Greater Flag */
	uint32_t G;
	/* Lesser Than Flag */
	uint32_t L;
	/* VMM Flag */
	bool VMM;
};
typedef struct FFLAGS FFLAGS_t;
typedef struct FVM_REGISTERS FVM_REGISTERS_t;
typedef struct sVM_api {
	void (*VM_printf)(const char* s, ...);
	SDL_Surface* (*VM_get_surface)(void);
	uint32_t* (*VM_get_memory_buffer)(void);
	FVM_REGISTERS_t* (*VM_get_regs)(void);
	FFLAGS_t* (*VM_get_flags)(void);
	void (*VM_set_resolution)(int x, int y, int col);
} VM_api_t;
VM_api_t VM_API;
void lib_init(void* vm_printf_ptr, void* vm_get_surface, void* vm_get_mem, void* vm_get_regs, void* vm_get_flags, void* vm_set_res)
{
	VM_API.VM_printf = vm_printf_ptr;
	VM_API.VM_get_surface = vm_get_surface;
	VM_API.VM_get_memory_buffer = vm_get_mem;
	VM_API.VM_get_regs = vm_get_regs;
	VM_API.VM_get_flags = vm_get_flags; 
	VM_API.VM_set_resolution = vm_set_res;
}
#endif
