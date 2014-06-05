/** FVM - Flouronix Virtual Machine **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <fvm/error.h>
#include <fvm/version.h>
#include <fvm/cpu/cpu.h>
#include <fvm/cpu/fault.h>
#include <fvm/cpu/idt.h>
#include <fvm/cpu/mem/memory.h>
#include <fvm/cpu/opcodes.h>
#include <fvm/rom/rom.h>
#include <fvm/fcall/fcall.h>
#include <fvm/cpu/registers.h>
#ifdef __USE_GRAPHICS
#include <fvm/sdl.h>
#endif
// FVM IDT
FVM_IDT_HANDLER_t FVM_IDTR[256];
// FVM Timer
clock_t FVM_TIMER = 0;
int StackCount = 0;
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
		printf("\nFVM - Flouronix Virtual Machine Version [%s]\nUsage: fvm [memory (bytes)] [ROM File]", FVM_VER);
		FVM_EXIT(FVM_NO_ERR);
	}
	//! Proccess command line arguments
	uint32_t total_mem = atoi(argv[1]);
	const char* exec_name = argv[2];
	#ifdef __USE_GRAPHICS
	SDL_EnableUNICODE(1);
	FVM_SDL_init(GL_MAX_X, GL_MAX_Y, GL_COLOR);
	GL_SURFACE_t* bmp = FVM_SDL_loadbmp("init.bmp");
	if (bmp == NULL)
	{
		printf("\nF**K OFF, 'init.bmp' is missing");
		FVM_EXIT(FVM_RESOURCE_ERR);
	}
	FVM_SDL_updatedisplay(bmp);
	bmpfont = FVM_SDL_loadbmp("font.bmp");
	if (bmpfont == NULL)
	{
		printf("\nF**K OFF, 'font.bmp' is missing");
		FVM_EXIT(FVM_RESOURCE_ERR);
	}
	FVM_SDL_setwincaption("Flouronix VM (Running)");
	SDL_printf(bmpfont, screen, "FVM %s Running.......\n", FVM_VER);
	screen_x = 0;
	FVM_SDL_updatedisplay(screen);
	#endif
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
	printf("\nAllocating Memory for FFLAGS");
	FFLAGS_t* CPU_Flags = (FFLAGS_t*)malloc(sizeof(FFLAGS_t));
	printf("\nFFLAGS Allocation Complete Address = [%p]", (void*)CPU_Flags);
	printf("\nFVM Initialization Complete.");
	printf("\nPreparing to allocate memory for emulator");
	FVM_MEM_t* CPU_memory = (FVM_MEM_t*)malloc(sizeof(FVM_MEM_t));
	FVM_BYTE_t* PhysicalMEM = (FVM_BYTE_t*)malloc(total_mem); 
	CPU_memory->MEM_START = PhysicalMEM;
	CPU_memory->MEM_SIZE = total_mem;
	printf("\nEmulator has allocated Memory, Memory Address = [%p], Memory Range = [%d]", (void *)CPU_memory->MEM_START, CPU_memory->MEM_SIZE);
	printf("\nPreparing to load ROM into memory....");
	printf("\nROM Image Address to be loaded at: [%d], ROM Name: [%s]", 0x0000, exec_name);
	loadrom(exec_name, PhysicalMEM, total_mem);
	CPU_regs->r11 = 0;
	printf("\nROM Loaded, \n");
	#ifndef __USE_GRAPHICS
	printf("Program Output:\n");
	#else
	printf("Program Output : In Graphics Mode (Please see SDL Window instead of Console");
	#endif
	printf("\7"); 
	FVM_TIMER = clock();
	while(CPU_regs->ON == 0x0001)
	{
		//! Any pending clocks?
		if(((clock() - FVM_TIMER) / (CLOCKS_PER_SEC/10000)) >= 1 && FVM_IDTR[1].address != 0)
		{
			CPU_regs->r11 = CPU_regs->r11;
			uint32_t returnaddress2 = CPU_regs->r11;
			PhysicalMEM[CPU_regs->r12] = returnaddress2;
			CPU_regs->r12--;
			StackCount++;
			CPU_regs->r11 = FVM_IDTR[1].address;
			FVM_TIMER = clock();
		}
		//keycode = 0;
		//! Query for SDL Event
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				FVM_EXIT(FVM_NO_ERR);
			}
			//If a key was pressed
            		//else if(event.type == SDL_KEYDOWN)
            		//{
			//	SDL_EnableUNICODE( SDL_ENABLE );
				//keycode = (char)event.key.keysym.unicode;
			//}
		}
		
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
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r0 = CPU_regs->r1;
					CPU_regs->r11 += 2;
					break;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r0 = CPU_regs->r2;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					CPU_regs->r0 = CPU_regs->r12;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r0 = CPU_regs->r3;
					CPU_regs->r11 += 2;
					break;	
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r0 = CPU_regs->r4;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r0 = CPU_regs->r5;
					CPU_regs->r11 += 2;
					break;
				}
				CPU_regs->r0 = PhysicalMEM[CPU_regs->r11+1];
				CPU_regs->r11 += 2;
				break;
			//! LD1 Load R1
			//! ld1 value
			case FVM_LD1:
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r1 = CPU_regs->r0;
					CPU_regs->r11 += 2;
					break;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r1 = CPU_regs->r2;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					CPU_regs->r1 = CPU_regs->r12;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r1 = CPU_regs->r3;
					CPU_regs->r11 += 2;
					break;	
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r1 = CPU_regs->r4;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r1 = CPU_regs->r5;
					CPU_regs->r11 += 2;
					break;
				}
				CPU_regs->r1 = PhysicalMEM[CPU_regs->r11+1];
				CPU_regs->r11 += 2;
				break;
			/* LD2 -- Load R2 */
			case FVM_LD2:
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r2 = CPU_regs->r0;
					CPU_regs->r11 += 2;
					break;
				}
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r2 = CPU_regs->r1;
					CPU_regs->r11 += 2;
					break;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					CPU_regs->r2 = CPU_regs->r12;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r2 = CPU_regs->r3;
					CPU_regs->r11 += 2;
					break;	
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r2 = CPU_regs->r4;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r2 = CPU_regs->r5;
					CPU_regs->r11 += 2;
					break;
				}
				CPU_regs->r2 = PhysicalMEM[CPU_regs->r11+1];
				CPU_regs->r11 += 2;
				break;
			/* LD3 Load R3 */
			case FVM_LD3:
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r3 = CPU_regs->r0;
					CPU_regs->r11 += 2;
					break;
				}
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r3 = CPU_regs->r1;
					CPU_regs->r11 += 2;
					break;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					CPU_regs->r3 = CPU_regs->r12;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r3 = CPU_regs->r4;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r5 = CPU_regs->r5;
					CPU_regs->r11 += 2;
					break;
				}
				CPU_regs->r3 = PhysicalMEM[CPU_regs->r11+1];
				CPU_regs->r11 += 2;
				break;
			/* LD4 - Load R4 */
			case FVM_LD4:
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r4 = CPU_regs->r0;
					CPU_regs->r11 += 2;
					break;
				}
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r4 = CPU_regs->r1;
					CPU_regs->r11 += 2;
					break;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					CPU_regs->r4 = CPU_regs->r12;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r4 = CPU_regs->r3;
					CPU_regs->r11 += 2;
					break;	
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r4 = CPU_regs->r5;
					CPU_regs->r11 += 2;
					break;
				}
				CPU_regs->r4 = PhysicalMEM[CPU_regs->r11+1];
				CPU_regs->r11 += 2;
				break;
			/* LD5 - Load R5 */
			case FVM_LD5:
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r5 = CPU_regs->r0;
					CPU_regs->r11 += 2;
					break;
				}
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r5 = CPU_regs->r1;
					CPU_regs->r11 += 2;
					break;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					CPU_regs->r5 = CPU_regs->r12;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r5 = CPU_regs->r3;
					CPU_regs->r11 += 2;
					break;	
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r5 = CPU_regs->r4;
					CPU_regs->r11 += 2;
					break;
				}
				CPU_regs->r5 = PhysicalMEM[CPU_regs->r11+1];
				CPU_regs->r11 += 2;
				break;
			/* LD12 -- Load Stack Pointer */
			case FVM_LD12:
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r12 = CPU_regs->r0 / 4;
					CPU_regs->r11 += 2;
					break;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r12 = CPU_regs->r1 / 4;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r12 = CPU_regs->r2 / 4;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r12 = CPU_regs->r3 / 4;
					CPU_regs->r11 += 2;
					break;	
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r12 = CPU_regs->r4 / 4;
					CPU_regs->r11 += 2;
					break;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r12 = CPU_regs->r5 / 4;
					CPU_regs->r11 += 2;
					break;
				}
				CPU_regs->r12 = PhysicalMEM[CPU_regs->r11+1] / 4;
				CPU_regs->r11 += 2;
				break;
			/* PUSH -- Push to the stack pointer */
			case FVM_PUSH:
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					PhysicalMEM[CPU_regs->r12] = CPU_regs->r0;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1) {
					PhysicalMEM[CPU_regs->r12] = CPU_regs->r1;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					PhysicalMEM[CPU_regs->r12] = CPU_regs->r2;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					PhysicalMEM[CPU_regs->r12] = CPU_regs->r3;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					PhysicalMEM[CPU_regs->r12] = CPU_regs->r4;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					PhysicalMEM[CPU_regs->r12] = CPU_regs->r5;
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					PhysicalMEM[CPU_regs->r12] = CPU_regs->r12;
				}
				else {
					PhysicalMEM[CPU_regs->r12] = PhysicalMEM[CPU_regs->r11+1];
				}
				CPU_regs->r12--;
				StackCount++;
				if (StackCount >= NewCPU_state->stack_limit)
				{
					printf("\nR12 : [%d]", CPU_regs->r12);
					printf("\n>>>>>>Stack F**K Up. Exitting Emulator\n");
					FVM_EXIT(FVM_STACK_ERR);
				}
				CPU_regs->r11 += 2;
				break;
			/* Pop out something from the stack into Reg */
			case FVM_POPR:
				if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)	
				{
						CPU_regs->r0 = PhysicalMEM[CPU_regs->r12+1];
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
						CPU_regs->r1 = PhysicalMEM[CPU_regs->r12+1];
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r2 = PhysicalMEM[CPU_regs->r12+1];
				}	
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r3 = PhysicalMEM[CPU_regs->r12+1];
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r4 = PhysicalMEM[CPU_regs->r12+1];
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r5 = PhysicalMEM[CPU_regs->r12+1];
				}
				else if (PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					CPU_regs->r12 = PhysicalMEM[CPU_regs->r12+1];
				}
						CPU_regs->r12++;
						StackCount--;
				if (StackCount < 0)
				{
					
					printf("\n>>>>>F**K UP: STACK COUNT IS UNDER ZERO (0) : [%d] R12 : [%d]\n", StackCount, CPU_regs->r12);
				}
				CPU_regs->r11 += 2;
				break;
			//! FCALL - Call the operating system
			//! fcall call_number
			case FVM_FCALL:
				CPU_regs->r11 = CPU_regs->r11;
				int a = fcall(PhysicalMEM[CPU_regs->r11+1], CPU_regs->r1, CPU_regs->r0, CPU_regs->r2);
				if (a == -2)
				{
					CPU_regs->r1 = 0;
				}
				else if (a == FCALL_READ)
				{
					CPU_regs->r1 = 0;
					CPU_regs->r1 = keycode;
				}
				CPU_regs->r11 += 2;
				break;
			//! JTX - Jump to Address X
			//! jtx address
			case FVM_JTX:
				CPU_regs->r11 = PhysicalMEM[CPU_regs->r11+1] / 4;
				break;
			case FVM_DEBUG:
				printf("\033[31m");
				printf("\n>>>>>>DEBUG Instruction OPCODE:{%d} Executed, Will print CPU status: \n>R0 : [%d]\n>R1 : [%d]\n>R2 : [%d]\n>R3 [%d]\n>R4: [%d]\nR5 [%d]\n>R17 : [%d]\n>R12 : [%d]\n>R11 : [%d]\nE : [%d]\nG : [%d]\nL : [%d]\n", FVM_DEBUG, CPU_regs->r0, CPU_regs->r1, CPU_regs->r2, CPU_regs->r3, CPU_regs->r4, CPU_regs->r5, CPU_regs->r17, CPU_regs->r12, CPU_regs->r11, CPU_Flags->E, CPU_Flags->G, CPU_Flags->L);
				printf("Memory Contents: \n");
				uint8_t* tmp = (uint8_t*)PhysicalMEM;
				uint32_t i = 0;
				for (i = 0; i < total_mem; ++i)
				{
					printf(" %c", tmp[i]);
				} 
				printf("\033[0m");
				CPU_regs->r11++;	
				break;
			/* LD1FA0 - Load R1 from address of R0, Loads a BYTE from address R0, and increments R0 */
			case FVM_LD1FA0:
				/* Null out R1 */
				CPU_regs->r1 = 0x00000000;
				CPU_regs->r11 = CPU_regs->r11;
				uint8_t* tmp2 = (uint8_t*)PhysicalMEM;
				CPU_regs->r1 = tmp2[CPU_regs->r0];
				CPU_regs->r11++;
				CPU_regs->r0++;
				break;
			/* Jumps to a procedure whose address is in R2 */
			case FVM_CALL:
				CPU_regs->r11 = CPU_regs->r11;
				uint32_t returnaddress = CPU_regs->r11 + 2;
				PhysicalMEM[CPU_regs->r12] = returnaddress;
				CPU_regs->r11 = PhysicalMEM[CPU_regs->r11+1] / 4;
				CPU_regs->r12--;
				StackCount++;
				//printf("\nR12: [%d]", CPU_regs->r12);
				//CPU_regs->r17 = CPU_regs->r11 + 2;
				//CPU_regs->r11 = PhysicalMEM[CPU_regs->r11+1] / 4;
				break;
			/* Returns from a procedure done by FVM_CALL*/
			case FVM_RET:
				//CPU_regs->r11 = CPU_regs->r17;
				//CPU_regs->r17 = 0;
				CPU_regs->r11 = PhysicalMEM[CPU_regs->r12+1];
				CPU_regs->r12++;
				///printf("\nR12: [%d]", CPU_regs->r12);
				StackCount--;
				break;
			/* CMPR - Compare Register with value */
			case FVM_CMPV:
				CPU_regs->r11 = CPU_regs->r11;
				int32_t value = PhysicalMEM[CPU_regs->r11+1+1];
				int32_t EVAL1 = PhysicalMEM[CPU_regs->r11+1];
				if (value == OPCODE_R0)
				{
					value = CPU_regs->r0;
				}
				else if (value == OPCODE_R1)
				{
					value = CPU_regs->r1;
				}
				else if (value == OPCODE_R2)
				{
					value = CPU_regs->r2;	
				}
				else if (value == OPCODE_R3)
				{
					value = CPU_regs->r3;
				}
				else if (value == OPCODE_R4)
				{
					value = CPU_regs->r4;	
				}
				else if (value == OPCODE_R5)
				{
					value = CPU_regs->r5;	
				}
				// Check the comparision operand
				if (EVAL1 == OPCODE_R0)
				{
					EVAL1 = CPU_regs->r0;
				}
				else if(EVAL1 == OPCODE_R1)
				{
					EVAL1 = CPU_regs->r1;
				}
				else if(EVAL1 == OPCODE_R2)
				{
					EVAL1 = CPU_regs->r2;
				}
				else if(EVAL1 == OPCODE_R3)
				{
					EVAL1 = CPU_regs->r3;
				}
				else if(EVAL1 == OPCODE_R4)
				{
					EVAL1 = CPU_regs->r4;
				}
				else if(EVAL1 == OPCODE_R5)
				{
					EVAL1 = CPU_regs->r5;
				}
				// Do the actual comparision
				if (EVAL1 == value)
				{
						CPU_Flags->E = 1;
						CPU_Flags->G = 0;
						CPU_Flags->L = 0;
				}
				else if (EVAL1 < value)
				{
						CPU_Flags->E = 0;	
						CPU_Flags->G = 0;			
						CPU_Flags->L = 1;
				}		
				else if (EVAL1 > value)
				{
						CPU_Flags->E = 0;
						CPU_Flags->G = 1;
						CPU_Flags->L = 0;		
				}
				CPU_regs->r11 += 3;
				break;
			/* JEX - Jump if Equal Flag is SET */
			case FVM_JEX:
					if(CPU_Flags->E == 1)
					{
						CPU_regs->r11 = PhysicalMEM[CPU_regs->r11+1] / 4;
						break;
					}
					else {
						CPU_regs->r11 += 2;
						break;
					}
			/* JGX - Jump if Greater than flag is set */
			case FVM_JGX:
					if (CPU_Flags->G == 1)
					{
						CPU_regs->r11 = PhysicalMEM[CPU_regs->r11+1] / 4;
						break;
					}
					else {
						CPU_regs->r11 += 2;
						break;
					}
			/* JLX - Jump if lesser than flag is set */
			case FVM_JLX:
					if (CPU_Flags->L == 1)
					{
						CPU_regs->r11 = PhysicalMEM[CPU_regs->r11+1] / 4;
						break;
					}
					else {
						CPU_regs->r11 += 2;
						break;
					}
			/* ST1TA0 - Store R1 to adddress of R0 (BYTE!) */
			case FVM_ST1TA0:
				CPU_regs->r11 = CPU_regs->r11;
				uint8_t* tmp3 = (uint8_t*)PhysicalMEM;
				tmp3[CPU_regs->r0] = (uint8_t)CPU_regs->r1;
				printf("%c", tmp3[CPU_regs->r0]);
				CPU_regs->r11++;
				CPU_regs->r0++;
				break;
			/* Interrupt - Interrupt the processor */	
			case FVM_INT:
				CPU_regs->r11 = CPU_regs->r11;
				uint32_t returnaddress1 = CPU_regs->r11 + 2;
				PhysicalMEM[CPU_regs->r12] = returnaddress1;
				CPU_regs->r12--;
				StackCount++;
				uint32_t inum = PhysicalMEM[CPU_regs->r11+1]; 
				CPU_regs->r11 = FVM_IDTR[inum].address;
				break;
			/* Register interrupt Handler */
			/* R0 : Interrupt number */
			/* R1 : Interrupt Handler Address */
			case FVM_LITH:
				FVM_IDTR[CPU_regs->r0].address = CPU_regs->r1 / 4;
				CPU_regs->r11++;
				break;
			/* IRETX - Return from interrupt */
			case FVM_IRETX:
				CPU_regs->r11 = PhysicalMEM[CPU_regs->r12+1];
				CPU_regs->r12++;
				StackCount--;
				break;
			/* INCR - Increment Reigster */
			case FVM_INCR:
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r0++;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r1++;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r2++;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r3++;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r4++;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r5++;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					CPU_regs->r12++;
				}
				CPU_regs->r11 += 2;
				break;
			/* DECR - Decrement Register */
			case FVM_DECR:
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r0--;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r1--;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r2--;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r3--;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r4--;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r5--;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					CPU_regs->r12--;
				}
				CPU_regs->r11 += 2;
				break;
			default:
				printf("\n>>>>>>Emulator Halted by unknown opcode: [0x%X] R11: [0x%X]. Shutting Down....",PhysicalMEM[CPU_regs->r11], CPU_regs->r11);
				CPU_regs->ON = 0x0000;
				FVM_EXIT(FVM_PROGRAM_ERR);
		}
	}	
	printf("\nEXIT(1) Called by program");
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
