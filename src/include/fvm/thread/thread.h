#ifndef __THREAD_H
#define __THREAD_H
#include <stdint.h>
#include <stdbool.h>
#include <fvm/cpu/cpu.h>
/** Structure to store thread information **/
typedef struct sVM_thread {
	FVM_REGISTERS_t* Thread_regs;
	FFLAGS_t* Thread_flags;
	bool is_used;
} VM_thread_t;
void init_thread(uint32_t ip, uint32_t sp);
uint32_t returnIP(int index);
VM_thread_t* returnThreadifrunning(int index);
int return_number_of_threads(void);
int create_thread(uint32_t sp, uint32_t ip);
int destroy_thread(int index);
extern VM_thread_t Thread_queue[4096];
#endif
