/** FVM - Flouronix Virtual Machine **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include <time.h>
#include <fvm/bitutils.h>
#include <fvm/error.h>
#include <fvm/version.h>
#include <fvm/cpu/cpu.h>
#include <fvm/cpu/fault.h>
#include <fvm/cpu/idt.h>
#include <fvm/cpu/mem/memory.h>
#include <fvm/cpu/mem/vmm.h>
#include <fvm/cpu/opcodes.h>
#include <fvm/rom/rom.h>
#include <fvm/fcall/fcall.h>
#include <fvm/cpu/registers.h>
#include <fvm/cpu/ports.h>
#include <fvm/gpu/gpu.h>
#include <fvm/fv11/fv11.h>
#include <fvm/tweaks.h>
#ifdef _USE_PTHREAD
#include <pthread.h>
#endif
#ifdef __USE_GRAPHICS
#include <fvm/sdl.h>
#endif
void* SDL_PollThread(void);
// FVM IDT
FVM_IDT_HANDLER_t FVM_IDTR[0xFF];
// FVM IO Address Space
FVM_PORT_t FVM_IOADDR_SPACE[0xFF];
// FVM Vtable
V_TABLE_t* vtable = 0;
// FVM Timer
clock_t FVM_TIMER = 0;
int StackCount = 0;
#ifdef _USE_PTHREAD
pthread_t* sdl_poll_thread;
#endif
//! Start point of the Emulator
int main (int argc, const char *argv[])
{
	printf("Processing Command Line Arguments...\n");
	if (argc < FVM_MIN_ARGS)
	{
		//! F**K OFF
		printf("F**K OFF., FVM_ERR[%d]\n", FVM_NO_ARG_ERR);
		printf("FVM - Flouronix Virtual Machine Version [%s]\nUsage: fvm [memory] [ROM File]\n", FVM_VER);
		FVM_EXIT(FVM_FATAL_ERR);
	}
	if(strcmp(argv[1], "-v") == 0)
	{
			printf("FVM Version : %s\n", FVM_VER);
			FVM_EXIT(FVM_NO_ERR);
	}
	else if(strcmp(argv[1], "-h") == 0) {
		printf("FVM - Flouronix Virtual Machine Version [%s]\nUsage: fvm [memory (bytes)] [ROM File]\n", FVM_VER);
		FVM_EXIT(FVM_NO_ERR);
	}
	//! Proccess command line arguments
	uint32_t total_mem = atoi(argv[1]);
	const char* exec_name = argv[2];
	#ifdef __USE_GRAPHICS
	SDL_EnableUNICODE(1);
	FVM_SDL_init(GL_MAX_X, GL_MAX_Y, GL_COLOR);
	GL_SURFACE_t* bmp = FVM_SDL_loadbmp("init.bmp");
	assert(bmp != NULL);
	FVM_SDL_updatedisplay(bmp);
	bmpfont = FVM_SDL_loadbmp("font.bmp");
	assert(bmpfont!=NULL);
	FVM_SDL_setwincaption("Flouronix VM (Running)");
	SDL_printf(bmpfont, screen, "FVM %s Running.......\n", FVM_VER);
	screen_x = 0;
	FVM_SDL_updatedisplay(screen);
	#endif
	#ifdef _USE_PTHREAD
	pthread_create(&sdl_poll_thread, NULL, &SDL_PollThread, NULL);
	#endif
	printf("FVM Version : %s, Requested Emulator Memory: %u, Requested ROM File: %s\n", FVM_VER, total_mem, exec_name);
	printf("Creating New FVM CPU......\n");
	//! Create a new CPU
	FVM_CPU_t* NewCPU = (FVM_CPU_t*)malloc(sizeof(FVM_CPU_t));
	printf("Allocated Memory for CPU struct, address: %p\n", (void*)NewCPU);
	//! Create a CPU state
	printf("Now Creating New CPU state.....\n");
	FVM_CPU_STATE_t* NewCPU_state = (FVM_CPU_STATE_t*)malloc(sizeof(FVM_CPU_STATE_t));
	printf("CPU State Created, address : %p\n", (void*)NewCPU_state);
	//! Set CPU to Default State
	NewCPU_state->interrupts_enabled = true; //! Enable Interrupts
	NewCPU_state->fpu_present = false; //! No FPU present
	NewCPU_state->stack_limit = total_mem; //! Maximum stack limit
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
	/* Configure r12 to be the end of memory */
	CPU_regs->r12 = (FVM_REG_t)total_mem;
	CPU_regs->ON = 0x0001;
	//! Fault register must be configured
	CPU_regs->r16 = E_NOERR; //! Reacts violently to ALL CAPS :)
	//! Now initialize the CPU
	NewCPU->CPU_REGS = CPU_regs;
	NewCPU->CPU_STATE = NewCPU_state;
	printf("Allocating Memory for FFLAGS\n");
	FFLAGS_t* CPU_Flags = (FFLAGS_t*)malloc(sizeof(FFLAGS_t));
	CPU_Flags->VMM = false;
	printf("FFLAGS Allocation Complete Address = [%p]\n", (void*)CPU_Flags);
	printf("FVM Initialization Complete.\n");
	printf("Preparing to allocate memory for emulator\n");
	FVM_MEM_t* CPU_memory = (FVM_MEM_t*)malloc(sizeof(FVM_MEM_t));
	uint8_t* MemoryAllocate = (uint8_t*)malloc(total_mem);
	//FVM_BYTE_t* PhysicalMEM = (FVM_BYTE_t*)malloc(total_mem); 
	FVM_BYTE_t* PhysicalMEM = (FVM_BYTE_t*)&MemoryAllocate[0];
	CPU_memory->MEM_START = PhysicalMEM;
	CPU_memory->MEM_SIZE = total_mem;
	printf("Emulator has allocated Memory, Memory Address = [%p], Memory Range = [%d]\n", (void *)CPU_memory->MEM_START, CPU_memory->MEM_SIZE);
	printf("Preparing to load ROM into memory....\n");
	printf("ROM Image Address to be loaded at: [%d], ROM Name: [%s]\n", 0x0000, exec_name);
	loadrom(exec_name, PhysicalMEM, total_mem);
	CPU_regs->r11 = 0;
	printf("\nROM Loaded, \n");
	#ifndef __USE_GRAPHICS
	printf("Program Output:\n");
	#else
	printf("Program Output : In Graphics Mode (Please see SDL Window instead of Console)\n");
	#endif
	printf("\7"); 
	FVM_TIMER = clock();
	/** Blank out the header **/
	// PhysicalMEM[0] = FVM_SLP;
	FV11_RETURN_t* retval = fv11_load(PhysicalMEM, total_mem);
	CPU_regs->r11 = retval->r11;
	CPU_regs->r12 = retval->sp;
	printf("R11: [%d] and SP: [%d]\n", CPU_regs->r11, CPU_regs->r12);
	while(CPU_regs->ON == 0x0001)
	{
		//! Any pending clocks?
		if(((clock() - FVM_TIMER) / (CLOCKS_PER_SEC/10000)) >= 1 && FVM_IDTR[1].address != 0 && NewCPU_state->interrupts_enabled == true)
		{
			CPU_regs->r11 = CPU_regs->r11;
			uint32_t returnaddress2 = CPU_regs->r11;
			PhysicalMEM[CPU_regs->r12] = returnaddress2;
			CPU_regs->r12--;
			StackCount++;
			CPU_regs->r11 = FVM_IDTR[1].address;
			FVM_TIMER = clock();
		}
		// Emulate instruction then
		emulate_FVM_instruction(CPU_regs, NewCPU_state, CPU_Flags, FVM_IOADDR_SPACE, PhysicalMEM, FVM_IDTR, vtable);
	}
	printf("EXIT(1)\n");
	FVM_SDL_setwincaption("Flouronix VM (Dormant)");
	int END = 0;
	while (END == 0)
	{
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				END = 1;
			}
			else {
				//! Do nothing
			}
		}
	}
	free(NewCPU);
	free(NewCPU_state);
	free(CPU_regs);
	free(CPU_memory);
	free(PhysicalMEM);
	FVM_EXIT(FVM_NO_ERR);
	//! Just in case if we haven't rescheduled
	return FVM_NO_ERR;
	for(;;);
}
// SDL Thread the can be used for polling exits
void* SDL_PollThread(void)
{
	while(1)
	{
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				FVM_EXIT(FVM_NO_ERR);
			}
		}
		else {
		}
	}
}
