#include <stdint.h>
#include <stdlib.h>
#include <fvm/cpu/cpu.h>
#include <fvm/gpu/gpu.h>
#include <fvm/gpu/opcodes.h>
/* GPU of the FVM Machine */
int gpu_emulate_instruction(GPU_REGS_t* GPU_REGS, FVM_MEM_t* Memory, CPU_REGS_t* CPU_REGS)
{
	switch(Memory[CPU_REGS->r11)
	{
		
	}
}
