#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fvm/cpu/cpu.h>
#include <fvm/thread/thread.h>
int no_of_threads = 4096;
VM_thread_t Thread_queue[4096];
void init_thread(uint32_t ip, uint32_t sp)
{	
	// Set all threads to unused
	for(int i = 0; i <= no_of_threads; i++)
	{
		Thread_queue[i].is_used = false;
	}
	// Create embryo thread
	Thread_queue[0].Thread_regs = (FVM_REGISTERS_t*)malloc(sizeof(FVM_REGISTERS_t));
	Thread_queue[0].Thread_flags = (FFLAGS_t*)malloc(sizeof(FFLAGS_t));
	Thread_queue[0].is_used = true;
	Thread_queue[0].Thread_regs->IP = ip;
	Thread_queue[0].Thread_regs->r12 = sp;	
	Thread_queue[0].Thread_regs->ON = 1;
	Thread_queue[0].Thread_regs->thread_local_storage = ip;
	printf("Embryo Thread Created!\n");
}
int create_thread(uint32_t ip, uint32_t sp)
{
	printf("$CREAT_THREAD: [%d] [%d]\n", sp, ip);
	
	for(int i = 0; i <= no_of_threads; i++)
	{	
		if(Thread_queue[i].is_used == false)
		{
			Thread_queue[i].Thread_regs = (FVM_REGISTERS_t*)malloc(sizeof(FVM_REGISTERS_t));
			Thread_queue[i].Thread_flags = (FFLAGS_t*)malloc(sizeof(FFLAGS_t));
			Thread_queue[i].Thread_regs->IP = ip;
			Thread_queue[i].Thread_regs->r12 = sp;	
			Thread_queue[i].Thread_regs->no = i;
			Thread_queue[i].Thread_regs->ON = 1;
			Thread_queue[0].Thread_regs->thread_local_storage = ip;
			Thread_queue[i].is_used = true;
			return i;
		}
	}
	return -1;
}
int destroy_thread(int index)
{
	for(int i = 0; i <= no_of_threads; i++)
	{
		if(i <= no_of_threads && i > 0 && Thread_queue[i].is_used == true && i == index)
		{
			Thread_queue[i].is_used = false;
			free(Thread_queue[i].Thread_regs);
			free(Thread_queue[i].Thread_flags);
			return 0;
		}
	}
	return -1;
}
uint32_t returnIP(int index)
{
	for(int i = 0; i <= no_of_threads; i++)
	{
		if(i == index && Thread_queue[i].is_used == true)
		{
			return Thread_queue[i].Thread_regs->IP;
		}
	}
	return -1;
}
VM_thread_t* returnThreadifrunning(int index)
{
	if(index <= no_of_threads && index > 0)
	{
		if(Thread_queue[index].is_used == true)
		{
			return &Thread_queue[index];
		}
	}
	return NULL;
}
int return_number_of_threads(void)
{
	return no_of_threads;
}

