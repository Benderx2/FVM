/** FVM - Fluoronix Virtual Machine **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <float.h>
#include <assert.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <fvm/native/native.h>
#include <fvm/bitutils.h>
#include <fvm/error.h>
#include <fvm/sighandle.h>
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
#include <fvm/initrd/initrd.h>
#include <fvm/fpu/fpu.h>
#include <fvm/gc/objects.h>
#include <fvm/thread/thread.h>
#include <fvm/cpu/m_cpu.h>
#include <fvm/mm/mm.h>
#include <fvm/devices/fgx.h>
#include <fvm/devices/ppu.h>
#include <fvm/v_stack/v_stack.h>
#ifdef _USE_PTHREAD
#include <pthread.h>
#endif
#ifdef __USE_GRAPHICS
#include <fvm/sdl.h>
#endif
void* SDL_PollThread(void);
uint32_t total_mem;
FVM_REGISTERS_t* CPU2_regs;
FFLAGS_t* CPU2_Flags;
// FVM IDT
FVM_IDT_HANDLER_t FVM_IDTR[0xFF];
// FVM IO Address Space
FVM_PORT_t FVM_IOADDR_SPACE[0xFF];
FVM_REGISTERS_t* CPU_regs;
FVM_BYTE_t* Memory32;
FFLAGS_t* CPU_Flags;
// FVM Vtable
V_TABLE_t* vtable = 0;
// FVM Timer
clock_t FVM_TIMER = 0;
int StackCount = 0;
FVM_CPU_STATE_t* NewCPU_state;
#ifdef _USE_PTHREAD
pthread_t* sdl_poll_thread;
#endif
//! Start point of the Emulator
int main (int argc, const char *argv[])
{	
	printf("Flouronix Virtual Machine (FVM) --- starting..\n");
	if(dup2(fileno(popen("tee stdout.txt", "w")), STDOUT_FILENO) < 0) {
        		printf("couldn't redirect output\n");
    	}
	// Load "embryo" shared object.
	if(argc == 2)
	{
		if(strcmp(argv[1], "-v") == 0)
		{
			printf("FVM Version : %s\n", FVM_VER);
			FVM_EXIT(FVM_NO_ERR);
		}
		else if(strcmp(argv[1], "-h") == 0) {
			printf("FVM - Flouronix Virtual Machine Version [%s]\nUsage: fvm [memory (bytes)] [ROM Disk Image] [ROM File Name]\n", FVM_VER);
			FVM_EXIT(FVM_NO_ERR);
		}
	}
	printf("Installing UNIX signal handlers....\n");
	/** Install the SIGSEGV handler **/
	signal(SIGSEGV, SIGSEGV_handler);
	/** SIGILL **/
	signal(SIGILL, SIGILL_handler);
	printf("Loading embryo library....\n");
	load_native_library("./embryo.so");
	printf("Initialising VM Stack Interface\n");
	init_stack();
	printf("Processing Command Line Arguments...\n");
	if (argc < FVM_MIN_ARGS)
	{
		//! F**K OFF
		printf("F**K OFF., FVM_ERR[%d]\n", FVM_NO_ARG_ERR);
		printf("FVM - Flouronix Virtual Machine Version [%s]\nUsage: fvm [memory] [ROM Disk Image] [ROM File]\n", FVM_VER);
		FVM_EXIT(FVM_FATAL_ERR);
	}
	//! Proccess command line arguments
	total_mem = atoi(argv[1]);
	#ifdef __USE_GRAPHICS
	SDL_EnableUNICODE(1);
	FVM_SDL_init(640, 480, 32);
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
	printf("FVM Version : %s, Requested Emulator Memory: %u, Requested ROM File: %s\n", FVM_VER, total_mem, argv[3]);
	printf("Creating New FVM CPU......\n");
	//! Create a new CPU
	FVM_CPU_t* NewCPU = (FVM_CPU_t*)malloc(sizeof(FVM_CPU_t));
	printf("Allocated Memory for CPU struct, address: %p\n", (void*)NewCPU);
	//! Create a CPU state
	printf("Now Creating New CPU state.....\n");
	NewCPU_state = (FVM_CPU_STATE_t*)malloc(sizeof(FVM_CPU_STATE_t));
	printf("CPU State Created, address : %p\n", (void*)NewCPU_state);
	//! Set CPU to Default State
	NewCPU_state->interrupts_enabled = true; //! Enable Interrupts
	NewCPU_state->fpu_present = true;
	NewCPU_state->stack_limit = total_mem; //! Maximum stack limit
	//! Zero all this out
	NewCPU_state->reserved0 = 0;
	NewCPU_state->reserved1 = 0;
	NewCPU_state->reserved2 = 0;
	NewCPU_state->reserved3 = 0;
	printf("CPU State Settings are to default, now allocating memory for CPU Registers\n");
	//! Initialize Registers
	CPU_regs = (FVM_REGISTERS_t*)malloc(sizeof(FVM_REGISTERS_t));
	CPU2_regs = (FVM_REGISTERS_t*)malloc(sizeof(FVM_REGISTERS_t));
	printf("Allocation Complete, now setting registers to default state.\n");
	/* Configure r12 to be the end of memory */
	CPU_regs->r12 = (FVM_REG_t)total_mem;
	CPU_regs->ON = 0x0001;
	//! Fault register must be configured
	CPU_regs->r16 = E_NOERR; //! Reacts violently to ALL CAPS :)
	//! Now initialize the CPU
	NewCPU->CPU_REGS = CPU_regs;
	NewCPU->CPU_STATE = NewCPU_state;
	printf("Allocating Memory for FFLAGS\n");
	CPU_Flags = (FFLAGS_t*)malloc(sizeof(FFLAGS_t));
	CPU2_Flags = (FFLAGS_t*)malloc(sizeof(FFLAGS_t));
	CPU_Flags->VMM = false;
	printf("FFLAGS Allocation Complete Address = [%p]\n", (void*)CPU_Flags);
	printf("FVM Initialization Complete.\n");
	printf("Preparing to allocate memory for emulator\n");
	FVM_MEM_t* CPU_memory = (FVM_MEM_t*)malloc(sizeof(FVM_MEM_t));
	uint8_t* MemoryAllocate = (uint8_t*)malloc(total_mem);
	// Initalize Memory Manager
	mm_init(MemoryAllocate, total_mem);
	//FVM_BYTE_t* Memory32 = (FVM_BYTE_t*)malloc(total_mem); 
	Memory32 = (FVM_BYTE_t*)&MemoryAllocate[0];
	CPU_memory->MEM_START = Memory32;
	CPU_memory->MEM_SIZE = total_mem;
	printf("Emulator has allocated Memory for program, Memory Address = [%p], Memory Range = [%d]\n", (void *)CPU_memory->MEM_START, CPU_memory->MEM_SIZE);
	printf("Preparing to load ROM into memory....\n");
	printf("ROM Image Address to be loaded at: [%d], ROM Name: [%s]\n", 0x0000, argv[3]);
	// Open Disk Image for reading (getting the file size)
	FILE* fp = fopen(argv[2], "r+b");
	if(fp == NULL)
	{
		printf("\n#error: ROM Disk Image not found\n");
		FVM_EXIT(FVM_ROM_ERR);
	}
	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	// Allocate memory for disk image
	uint8_t* buffer = malloc(sz);
	fseek(fp, 0L, SEEK_SET);
	load_disk_image(argv[2], buffer, sz);
	printf("Disk Image Reading Done.\n");
	// Load file from the Ram disk
	load_file_from_disk(MemoryAllocate, argv[3], buffer, total_mem);
	fclose(fp);
	FVM_TIMER = clock();
	FV11_RETURN_t* retval = fv11_load(Memory32, total_mem);
	CPU_regs->IP = retval->r11;
	CPU_regs->r12 = retval->sp;
	printf("IP: [%d] and SP: [%d]\n", CPU_regs->IP, CPU_regs->r12);
	printf("\nROM Loaded, \n");
	#ifndef __USE_GRAPHICS
	printf("Program Output:\n");
	#else
	printf("Program Output : In Graphics Mode (Please see SDL Window instead of Console)\n");
	#endif
	/** Create idle object **/
	printf("GC_INIT: Creating embryo object....\n");
	VM_CreateObject(INT_TYPE, OBJ_IDLE);
	printf("THREAD_INIT: Creating Embryo thread....\n");
	init_thread(CPU_regs->IP, CPU_regs->r12);
	// Initialize PPU
	init_ppu();
	UNUSED(CPU_Flags);
	UNUSED(CPU2_regs);
	UNUSED(CPU2_Flags);
	do_cpu();
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
	free(Memory32);
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
