/** FVM - Flouronix Virtual Machine **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <fvm/error.h>
#include <fvm/version.h>
#include <fvm/cpu/cpu.h>
#include <fvm/cpu/fault.h>
#include <fvm/cpu/mem/memory.h>
#include <fvm/cpu/opcodes.h>
#include <fvm/rom/rom.h>
#include <fvm/fcall/fcall.h>
//! Start point of the Emulator
int main (int argc, const char *argv[])
{
	printf("Processing Command Line Arguments...");
	if (argc < FVM_MIN_ARGS)
	{
		//! F**K OFF
		printf("\nF**K OFF., FVM_ERR[%d]", FVM_NO_ARG_ERR);
		printf("\nFVM - Flouronix Virtual Machine Version [%s]\nUsage: fvm [memory] [ROM File]", FVM_VER);
		FVM_EXIT(FVM_FATAL_ERR);
	}
	if(strcmp(argv[1], "-v") == 0)
	{
			printf("\nFVM Version : %s", FVM_VER);
			FVM_EXIT(FVM_NO_ERR);
	}
	else if(strcmp(argv[1], "-h") == 0) {
		printf("\nFVM - Flouronix Virtual Machine Version [%s]\nUsage: fvm [memory] [ROM File]", FVM_VER);
		FVM_EXIT(FVM_NO_ERR);
	}
	//! Proccess command line arguments
	uint32_t total_mem = atoi(argv[1]);
	const char* exec_name = argv[2];
	printf("\nFVM Version : %s, Requested Emulator Memory: %u, Requested ROM File: %s", FVM_VER, total_mem, exec_name);
	printf("\nCreating New FVM CPU......");
	//! Create a new CPU
	FVM_CPU_t* NewCPU = (FVM_CPU_t*)malloc(sizeof(FVM_CPU_t));
	printf("\nAllocated Memory for CPU struct, address: %p", (void*)NewCPU);
	//! Create a CPU state
	printf("\nNow Creating New CPU state.....");
	FVM_CPU_STATE_t* NewCPU_state = (FVM_CPU_STATE_t*)malloc(sizeof(FVM_CPU_STATE_t));
	printf("\nCPU State Created, address : %p", (void*)NewCPU_state);
	//! Set CPU to Default State
	NewCPU_state->interrupts_enabled = true; //! Enable Interrupts
	NewCPU_state->fpu_present = false; //! No FPU present
	NewCPU_state->stack_limit = 0xFFFF; //! Maximum stack limit
	//! Zero all this out
	NewCPU_state->reserved0 = 0;
	NewCPU_state->reserved1 = 0;
	NewCPU_state->reserved2 = 0;
	NewCPU_state->reserved3 = 0;
	printf("\nCPU State Settings are to default, now allocating memory for CPU Registers");
	//! Initialize Registers
	FVM_REGISTERS_t* CPU_regs = (FVM_REGISTERS_t*)malloc(sizeof(FVM_REGISTERS_t));
	printf("\nAllocation Complete, now setting registers to default state.");
	//! All general purpose registers must be 0
	CPU_regs->r0 = 0x0000;
	CPU_regs->r1 = 0x0000;
	/* GNU nano is cool */
	CPU_regs->r2 = 0x0000;
	CPU_regs->r3 = 0x0000;
	CPU_regs->r4 = 0x0000;
	CPU_regs->r5 = 0x0000;
	CPU_regs->r6 = 0x0000;
	CPU_regs->r7 = 0x0000;
	CPU_regs->r8 = 0x0000;
	CPU_regs->r9 = 0x0000;
	CPU_regs->r10 = 0x0000;
	CPU_regs->r11 = 0x0000;
	CPU_regs->ON = 0x0001;
	//! Fault register must be configured
	CPU_regs->r16 = E_NOERR; //! Reacts violently to ALL CAPS :)
	//! Now initialize the CPU
	NewCPU->CPU_REGS = CPU_regs;
	NewCPU->CPU_STATE = NewCPU_state;
	printf("\nFVM Initialization Complete.");
	printf("\nPreparing to allocate memory for emulator");
	FVM_MEM_t* CPU_memory = (FVM_MEM_t*)malloc(sizeof(FVM_MEM_t));
	uint16_t* PhysicalMEM = (uint16_t*)malloc(total_mem); 
	CPU_memory->MEM_START = PhysicalMEM;
	CPU_memory->MEM_SIZE = total_mem;
	printf("\nEmulator has allocated Memory, Memory Address = [%p], Memory Range = [%d]", (void *)CPU_memory->MEM_START, CPU_memory->MEM_SIZE);
	printf("\nPreparing to load ROM into memory....");
	printf("\nROM Image Address to be loaded at: [%d], ROM Name: [%s]", 0x0000, exec_name);
	loadrom(exec_name, PhysicalMEM, total_mem);
	printf("\nROM Loaded, now executing code!\nProgram Output:\n");
	while(CPU_regs->ON == 0x0001)
	{
		switch(PhysicalMEM[CPU_regs->r11])
		{
			//! Sleep
			//! slp
			case FVM_SLP:
				//! Increment R11
				CPU_regs->r11 += 1;
				break;
			//! Exit
			case FVM_EXT:
				CPU_regs->ON = 0x0000;
				break;
			//! LD0 - Load R0
			case FVM_LD0:
				CPU_regs->r0 = PhysicalMEM[CPU_regs->r11+1];
				CPU_regs->r11 += 2;
				break;
			//! LD1 Load R1
			//! ld1 value
			case FVM_LD1:
				CPU_regs->r1 = PhysicalMEM[CPU_regs->r11+1];
				CPU_regs->r11 += 2;
				break;
			//! FCALL - Call the operating system
			//! fcall call_number
			case FVM_FCALL:
				fcall(CPU_regs->r0, CPU_regs->r1);
				CPU_regs->r11 += 1;
				break;
			//! JTX - Jump to Address X
			//! jtx address
			case FVM_JTX:
				CPU_regs->r11 = PhysicalMEM[CPU_regs->r11+1];
				break;
			default:
				printf("\n>>>>>>Emulator Halted by unknown opcode: [0x%X] R11: [0x%X]. Shutting Down....",PhysicalMEM[CPU_regs->r11], CPU_regs->r11);
				CPU_regs->ON = 0x0000;
				FVM_EXIT(FVM_PROGRAM_ERR);
		}
	}
	//! Free Up Junk!
	free(NewCPU);
	free(NewCPU_state);
	free(CPU_regs);
	free(CPU_memory);
	free(PhysicalMEM);
	FVM_EXIT(FVM_NO_ERR);
	return FVM_NO_ERR;
}
