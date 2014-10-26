#include <fvm/cpu/m_cpu.h>
void do_cpu(void)
{
	while(CPU_regs->ON == 0x0001)
	{
		//! Any pending clocks?
		for(int i = 0; i < return_number_of_threads(); i++)
		{
			if(Thread_queue[i].is_used == false)
			{
				// Do nothing
			}
			else
			{
				CPU_regs = Thread_queue[i].Thread_regs;
				CPU_Flags = Thread_queue[i].Thread_flags;
				CPU_Flags->VMM = false;
				printf("CPU_regs : %p, CPU_Flags : %p, IP : %d, SP : %d\n",(void*)CPU_regs, (void*)CPU_Flags, CPU_regs->IP, CPU_regs->r12);
				if(((clock() - FVM_TIMER) / (CLOCKS_PER_SEC/10000)) >= 1 && FVM_IDTR[1].address != 0 && NewCPU_state->interrupts_enabled == true)
				{
					CPU_regs->IP = CPU_regs->IP;
					uint32_t returnaddress2 = CPU_regs->IP;
					Memory32[CPU_regs->r12] = returnaddress2;
					CPU_regs->r12--;
					StackCount++;
					CPU_regs->IP = FVM_IDTR[1].address;
					FVM_TIMER = clock();
				}
				emulate_FVM_instruction(CPU_regs, CPU2_regs, NewCPU_state, CPU_Flags, FVM_IOADDR_SPACE, Memory32, FVM_IDTR, vtable);
			}
		}
		// Emulate instruction then (Core I)
		if(CPU_regs->r17 == 1)
		{
			/** CORE II Wakeup message received **/
			emulate_FVM_instruction(CPU2_regs, CPU2_regs, NewCPU_state, CPU2_Flags, FVM_IOADDR_SPACE, Memory32, FVM_IDTR, vtable);
		}
	}
}
