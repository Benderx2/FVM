#ifndef __M_CPU_H
#define __M_CPU_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <fvm/cpu/cpu.h>
#include <fvm/cpu/ports.h>
#include <fvm/cpu/idt.h>
#include <fvm/cpu/mem/vmm.h>
#include <fvm/thread/thread.h>
extern FVM_IDT_HANDLER_t FVM_IDTR[0xFF];
extern FVM_PORT_t FVM_IOADDR_SPACE[0xFF];
extern FVM_BYTE_t* Memory32;
extern FFLAGS_t* CPU_Flags;
extern FVM_REGISTERS_t* CPU_regs;
extern FFLAGS_t* CPU2_Flags;
extern FVM_REGISTERS_t* CPU2_regs;
extern V_TABLE_t* vtable;
extern FVM_CPU_STATE_t* NewCPU_state;
extern clock_t FVM_TIMER;
extern int StackCount;
void do_cpu(void);
#endif
