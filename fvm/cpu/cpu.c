#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fvm/version.h>
#include <fvm/cpu/opcodes.h>
#include <fvm/cpu/registers.h>
#include <fvm/cpu/cpu.h>
#include <fvm/cpu/ports.h>
#include <fvm/cpu/mem/vmm.h>
#include <fvm/fcall/fcall.h>
#include <fvm/cpu/idt.h>
#include <fvm/error.h>
#include <fvm/sdl.h>
void emulate_FVM_instruction(FVM_REGISTERS_t* CPU_regs, FVM_CPU_STATE_t* NewCPU_state, FFLAGS_t* CPU_Flags, FVM_PORT_t* IOADDRSPACE, int32_t* PhysicalMEM,  FVM_IDT_HANDLER_t* FVM_IDTR, V_TABLE_t* vtable)
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
				/** Change CPU Registers to exit state **/
				CPU_regs->r0 = FVM_PROCESSOR_MODEL;
				CPU_regs->r1 = FVM_VERSION_MAJOR;
				CPU_regs->r2 = FVM_VERSION_MINOR;
				printf("R0 - Processor Model: %X\n", CPU_regs->r0);
				printf("R1 - FVM Version MAJOR: %X\n", CPU_regs->r1);
				printf("R2 - FVM Version Minor: %X\n", CPU_regs->r2);
				printf("R3, R4, R5, SP are zeroed, VM_EXIT()\n");
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
				//if (StackCount >= NewCPU_state->stack_limit)
				//{
				//	printf("\nR12 : [%X]", CPU_regs->r12);
				//	printf("\n>>>>>>Stack F**K Up. Exitting Emulator\n");
				//	FVM_EXIT(FVM_STACK_ERR);
				//}
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
					printf("\n>>>>>F**K UP: STACK COUNT IS UNDER ZERO (0) : [%X] R12 : [%X]\n", StackCount, CPU_regs->r12);
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
				printf("\n>>>>>>DEBUG Instruction OPCODE:{%X} Executed, Will print CPU status: \n>R0 : [%X]\n>R1 : [%X]\n>R2 : [%X]\n>R3 : [%X]\n>R4 : [%X]\n>R5 : [%X]\n>RX : [%X]\n>SP : [%X]\n>IP : [%X]\nEF : [%X]\nGF : [%X]\nLF : [%X]\n", FVM_DEBUG, CPU_regs->r0, CPU_regs->r1, CPU_regs->r2, CPU_regs->r3, CPU_regs->r4, CPU_regs->r5, CPU_regs->r17, CPU_regs->r12, CPU_regs->r11, CPU_Flags->E, CPU_Flags->G, CPU_Flags->L);
				//printf("Memory Contents: \n");
				//uint8_t* tmp = (uint8_t*)PhysicalMEM;
				//uint32_t i = 0;
				//for (i = 0; i < total_mem; ++i)
				//{
				//	printf(" %c", tmp[i]);
				//} 
				printf("\033[0m");
				CPU_regs->r11++;
				break;
			/* LD1FA0 - Load R1 from address of R0, Loads a BYTE from address R0, and increments R0 */
			case FVM_LD1FA0:
				CPU_regs->r11 = CPU_regs->r11;
				uint8_t* tmp2 = (uint8_t*)PhysicalMEM;
				if(CPU_Flags->VMM == true)
				{
					int32_t physaddr1 = vmm_virtual_to_physical(vtable, CPU_regs->r0);
					if(physaddr1 == -1)
					{
						printf("V_FAULT Exception triggered when CPU_flags->VMM is true!\n");
						FVM_EXIT(FVM_PROGRAM_ERR);
					}
					else {
						CPU_regs->r1 = tmp2[physaddr1];
					}
				}
				/* Null out R1 */
				CPU_regs->r1 = 0x00000000;
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
				//printf("\nR12: [%X]", CPU_regs->r12);
				//CPU_regs->r17 = CPU_regs->r11 + 2;
				//CPU_regs->r11 = PhysicalMEM[CPU_regs->r11+1] / 4;
				break;
			/* Returns from a procedure done by FVM_CALL*/
			case FVM_RET:
				//CPU_regs->r11 = CPU_regs->r17;
				//CPU_regs->r17 = 0;
				CPU_regs->r11 = PhysicalMEM[CPU_regs->r12+1];
				CPU_regs->r12++;
				///printf("\nR12: [%X]", CPU_regs->r12);
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
					if (CPU_Flags->L == 1 && CPU_Flags->VMM == false)
					{
						CPU_regs->r11 = PhysicalMEM[CPU_regs->r11+1] / 4;
						break;
					}
					else if(CPU_Flags->L == 1 && CPU_Flags->VMM == true)
					{
						CPU_regs->r11 = vmm_virtual_to_physical(vtable, PhysicalMEM[CPU_regs->r11+1]) / 4;
						if(CPU_regs->r11 == -1)
						{
							printf("V_FAULT()\n");
							FVM_EXIT(FVM_PROGRAM_ERR);
						}
					}
					else {
						CPU_regs->r11 += 2;
						break;
					}
			/* ST1TA0 - Store R1 to adddress of R0 (BYTE!) */
			case FVM_ST1TA0:
				CPU_regs->r11 = CPU_regs->r11;
				uint8_t* tmp3 = (uint8_t*)PhysicalMEM;
				if(CPU_Flags->VMM == true)
				{
					// Is Virtual Memory Enabled?
					// Then treat R0 as Virtual
					int32_t physaddr = vmm_virtual_to_physical(vtable, CPU_regs->r0);
					if(physaddr == -1)
					{
						printf("V_FAULT Exception triggered when CPU_flags->VMM is true!\n");
						FVM_EXIT(FVM_PROGRAM_ERR);
					}
					else {
						tmp3[physaddr] = (uint8_t)CPU_regs->r1;
					}
				}
				else {
					tmp3[CPU_regs->r0] = (uint8_t)CPU_regs->r1;
					printf("%c", tmp3[CPU_regs->r0]);
				}
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
			/* R1 : Interrupt Handler Address (Physical, Can be executed under VMM mode) */
			case FVM_LITH:
				if(CPU_Flags->VMM == true)
				{
					printf("V_FAULT Exception triggered when CPU_flags->VMM is true!\n");
					FVM_EXIT(FVM_PROGRAM_ERR);
				}
				FVM_IDTR[CPU_regs->r0].address = CPU_regs->r1 / 4;
				CPU_regs->r11++;
				break;
			/* IRETX - Return from interrupt */
			case FVM_IRETX:
				CPU_regs->r11 = PhysicalMEM[CPU_regs->r12+1];
				CPU_regs->r12++;
				printf("R12 [%X]\n", CPU_regs->r12);
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
			// Grab a DWORD from port
			case FVM_IN0:
				CPU_regs->r0 = IOADDRSPACE[CPU_regs->r11+1].in;
				CPU_regs->r11 += 2;
				break;
			/* Send a DWORD to port */
			case FVM_OUT0:
				IOADDRSPACE[CPU_regs->r11+1].out = CPU_regs->r0;
				CPU_regs->r11 += 2;
				break;
			case FVM_XOR:
				CPU_regs->r11 = CPU_regs->r11;
				int32_t XOR_VAL2;
				// XOR is done only on registers
				// Get the second operand first, as the first will be the destination.
				if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R0)
				{
					XOR_VAL2 = CPU_regs->r0;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R1)
				{
					XOR_VAL2 = CPU_regs->r1;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R2)
				{
					XOR_VAL2 = CPU_regs->r2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R3)
				{
					XOR_VAL2 = CPU_regs->r3;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R4)
				{
					XOR_VAL2 = CPU_regs->r4;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R5)
				{
					XOR_VAL2 = CPU_regs->r5;
				}
				else {
					XOR_VAL2 = PhysicalMEM[CPU_regs->r11+1+1];
				}
				// Get the first operand now and XOR() it with the second one.
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r0 = CPU_regs->r0 ^ XOR_VAL2;
					printf("XOR_VAL2: %X", XOR_VAL2);
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r1 = CPU_regs->r1 ^ XOR_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r2 = CPU_regs->r2 ^ XOR_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r3 = CPU_regs->r3 ^ XOR_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r4 = CPU_regs->r4 ^ XOR_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r5 = CPU_regs->r5 ^ XOR_VAL2;
				}
				else {
					printf("Invalid XOR(), undefined behaviour");
					CPU_regs->r11 += 3;
					break;
				}
				CPU_regs->r11 += 3;
				break;
			case FVM_MUL:
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r1;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r3;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r4;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r5;
				}
				else {
					CPU_regs->r0 = CPU_regs->r0 * PhysicalMEM[CPU_regs->r11+1];
				}
				CPU_regs->r11 += 2;
				break;
			case FVM_DIV:
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r1;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r3;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r4;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r5;
				}
				else {
					CPU_regs->r0 = CPU_regs->r0 * PhysicalMEM[CPU_regs->r11+1];
				}
				CPU_regs->r11 += 2;
				break;
			// Bitwise AND
			case FVM_AND:
				CPU_regs->r11 = CPU_regs->r11;
				int32_t AND_VAL2;
				if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R0)
				{
					AND_VAL2 = CPU_regs->r0;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R1)
				{
					AND_VAL2 = CPU_regs->r1;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R2)
				{
					AND_VAL2 = CPU_regs->r2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R3)
				{
					AND_VAL2 = CPU_regs->r3;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R4)
				{
					AND_VAL2 = CPU_regs->r4;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R5)
				{
					AND_VAL2 = CPU_regs->r5;
				}
				else {
					AND_VAL2 =  PhysicalMEM[CPU_regs->r11+1+1];
				}
				// Now set the operands appropriately
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r0 = CPU_regs->r0 & AND_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r1 = CPU_regs->r1 & AND_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r2 = CPU_regs->r2 & AND_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r3 = CPU_regs->r3 & AND_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r4 = CPU_regs->r4 & AND_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r5 = CPU_regs->r5 & AND_VAL2;
				}
				CPU_regs->r11 += 3;		
				break;
			// VMMINIT - Intialize Virtual Memory
			case FVM_VMMINIT:
				CPU_Flags->VMM = true;
				CPU_regs->r11++;
			// VMMQUIT - Deinitialize Virtual memory
			case FVM_VMMQUIT:
				CPU_Flags->VMM = false;
				CPU_regs->r11++;
			// STD - Store Register (DWORD) in addressof(R0)
			case FVM_STD:
				CPU_regs->r11 = CPU_regs->r11;
				uint8_t* tmp4 = (uint8_t*)PhysicalMEM;
				int32_t saver0 = CPU_regs->r0;
				if(CPU_Flags->VMM == true)
				{
					CPU_regs->r0 = vmm_virtual_to_physical(vtable, CPU_regs->r0);
				}
				uint32_t* dummy1 = (uint32_t*)&tmp4[CPU_regs->r0];
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					*dummy1 = CPU_regs->r0;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					*dummy1 = CPU_regs->r2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					*dummy1 = CPU_regs->r3;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					*dummy1 = CPU_regs->r4; 
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					*dummy1 = CPU_regs->r5;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					*dummy1 = CPU_regs->r12;
				}
				CPU_regs->r0 = saver0;
				CPU_regs->r11 += 2;
				break;
			// LDD - Load Register DWORD
			case FVM_LDD:
				CPU_regs->r11 = CPU_regs->r11;
				uint8_t* tmp5 = (uint8_t*)PhysicalMEM;
				int32_t saver0_1 = CPU_regs->r0;
				if(CPU_Flags->VMM == true)
				{	
					CPU_regs->r0 = vmm_virtual_to_physical(vtable, CPU_regs->r0);
				}
				uint32_t* dummy2 = (uint32_t*)&tmp5[CPU_regs->r0];
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					  CPU_regs->r0=*dummy2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					  CPU_regs->r2=*dummy2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					 CPU_regs->r3=*dummy2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					  CPU_regs->r4=*dummy2; 
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					 CPU_regs->r5= *dummy2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R12)
				{
					 CPU_regs->r12=*dummy2;
				}
				CPU_regs->r0 = saver0_1;
				CPU_regs->r11 += 2;
				break;
			// ADD - Add two registers, or a constant with a register
			case FVM_ADD:
				CPU_regs->r11 = CPU_regs->r11;
				int32_t ADD_VAL2;
				if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R0)
				{
					 ADD_VAL2 = CPU_regs->r0;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R1)
				{
					 ADD_VAL2 = CPU_regs->r1;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R2)
				{
					 ADD_VAL2 = CPU_regs->r2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R3)
				{
					 ADD_VAL2 = CPU_regs->r3;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R4)
				{
					 ADD_VAL2 = CPU_regs->r4;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R5)
				{
					 ADD_VAL2 = CPU_regs->r5;
				}
				else {
					 ADD_VAL2 =  PhysicalMEM[CPU_regs->r11+1+1];
				}
				// Now set the operands appropriately
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r0 = CPU_regs->r0 +  ADD_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r1 = CPU_regs->r1 +  ADD_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r2 = CPU_regs->r2 +  ADD_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r3 = CPU_regs->r3 +  ADD_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r4 = CPU_regs->r4 +  ADD_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r5 = CPU_regs->r5 +  ADD_VAL2;
				}
				printf(">>>>>>>LOG AND VAL 2 %d\n", ADD_VAL2);
				CPU_regs->r11 += 3;
				break;
			// Subtract 2 registers
			case FVM_SUB:
				CPU_regs->r11 = CPU_regs->r11;
				int32_t SUB_VAL2;
				if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R0)
				{
					 SUB_VAL2 = CPU_regs->r0;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R1)
				{
					 SUB_VAL2 = CPU_regs->r1;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R2)
				{
					 SUB_VAL2 = CPU_regs->r2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R3)
				{
					 SUB_VAL2 = CPU_regs->r3;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R4)
				{
					 SUB_VAL2 = CPU_regs->r4;
				}
				else if(PhysicalMEM[CPU_regs->r11+1+1] == OPCODE_R5)
				{
					 SUB_VAL2 = CPU_regs->r5;
				}
				else {
					 SUB_VAL2 =  PhysicalMEM[CPU_regs->r11+1+1];
				}
				// Now set the operands appropriately
				if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R0)
				{
					CPU_regs->r0 = CPU_regs->r0 -  SUB_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R1)
				{
					CPU_regs->r1 = CPU_regs->r1 - SUB_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R2)
				{
					CPU_regs->r2 = CPU_regs->r2 - SUB_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R3)
				{
					CPU_regs->r3 = CPU_regs->r3 - SUB_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R4)
				{
					CPU_regs->r4 = CPU_regs->r4 - SUB_VAL2;
				}
				else if(PhysicalMEM[CPU_regs->r11+1] == OPCODE_R5)
				{
					CPU_regs->r5 = CPU_regs->r5 - SUB_VAL2;
				}
				CPU_regs->r11 += 3;
				break;
			// V_LOAD - Load Virtual Address Table, pointer to address table MUST be 4-bytes aligned and must be physical...
			case FVM_V_LOAD:
					printf("WARNING! SYSTEM CONFIGURED V_TABLE WILL BE CHANGED. EXPECT UNDEFINED BEHAVIOUR!\n");
					printf("Checking if  System is in VMM Mode....\n");
					if(CPU_Flags->VMM == true)
					{
							printf("V_FAULT() triggered.");
							FVM_EXIT(FVM_PROGRAM_ERR);
					}
					else {
						printf("System is not under VMM Mode, going to set V_TABLE!");
						vtable = (V_TABLE_t*)(PhysicalMEM + PhysicalMEM[CPU_regs->r11+1]);
					}
					CPU_regs->r12 += 2;
					break;
			
			// LDSP - Load R1 from Stack Pointer Offset (i.e. LDSP 1 will load R1 from the first 4-bytes down the stack, LDSP 2 will load it from 8-bytes down the stack
			default:
				printf("\n>>>>>>Emulator Halted by unknown opcode: [0x%X] R11: [0x%X]. Shutting Down....",PhysicalMEM[CPU_regs->r11], CPU_regs->r11);
				CPU_regs->ON = 0x0000;
				FVM_EXIT(FVM_PROGRAM_ERR);
		}
			return;
	}
