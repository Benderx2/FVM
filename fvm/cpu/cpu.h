#ifndef __CPU_H
#define __CPU_H
#ifndef __cplusplus
//! C doesn't have bool support.
#include <stdbool.h>
#endif
#include <stdint.h>
typedef int32_t FVM_REG_t;
typedef uint8_t FVM_BYTE_t;
struct FVM_MEM {
	FVM_REG_t* MEM_START;
	uint32_t MEM_SIZE;
};
typedef struct FVM_MEM FVM_MEM_t;
// This is a structure for the CPU registers
// in an FVM Machine, there are a total of 15
// registers, each register is 16-bit, which means
// they occupy a total of 30 bytes :).
// Out of these 10 can only be used by programs,
// a.k.a GPRs (General Purpose Registers), the other
// 5 are used because:
// r11 - Instruction Pointer (CANNOT be modified by the program directly, Use CALL or JUMP)
// r12 - Stack Pointer (Points to the stack, DO NOT USE THIS FOR GENERAL STUFF unless you want your CALLS to be fucked)
// r13 - Base Pointer - Use it, but it's been reserved for C compilers and all that.
// r14 - CPU Status Register - Contains various information about the CPU or the firmware (Cannot change it)
// r15 - Hardware Status Register - Contains Various Information about the hardware
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
	FVM_REG_t r11;
	/* Stack Pointer */	
	FVM_REG_t r12;
	/* Base Pointer */
	FVM_REG_t r13;
	/* CPU Register */
	FVM_REG_t r14;
	/* Hardware status register */
	FVM_REG_t r15;
	/* Fault register */
	FVM_REG_t r16;
	/* ON Register */
	FVM_REG_t ON;
};
typedef struct FVM_REGISTERS FVM_REGISTERS_t;
struct FVM_CPU_STATE {
	// Processor Extensions and Interrupts
	bool interrupts_enabled;
	// Is an internal CPU present?
	bool fpu_present;
	// Stack Limit
	FVM_REG_t stack_limit;
	// Reserved
	uint32_t reserved0;	
	uint32_t reserved1;	
	uint32_t reserved2;
	uint32_t reserved3;
};
struct FFLAGS 
{
	/* Equal Flag */
	uint16_t E;
	/* Zero Flag */
	uint16_t Z;
	/* Greater Flag */
	uint16_t G;
	/* Lesser Than Flag */
	uint16_t L;
};
typedef struct FFLAGS FFLAGS_t;
typedef struct FVM_CPU_STATE FVM_CPU_STATE_t;
struct FVM_CPU {
	/* This is an instance of a new CPU */
	FVM_REGISTERS_t* CPU_REGS;
	/* CPU State (Interrupts etc.) */
	FVM_CPU_STATE_t* CPU_STATE;
};
typedef struct FVM_CPU FVM_CPU_t;
#endif
