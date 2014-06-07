#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fvm/cpu/opcodes.h>
#include <fvm/cpu/registers.h>
#include <fvm/cpu/cpu.h>
#include <fvm/cpu/ports.h>
#include <fvm/fcall/fcall.h>
#include <fvm/cpu/idt.h>
#include <fvm/error.h>
#include <fvm/sdl.h>
void emulate_FVM_instruction(FVM_REGISTERS_t* CPU_regs, FVM_CPU_STATE_t* NewCPU_state, FFLAGS_t* CPU_Flags, FVM_PORT_t* IOADDRSPACE, int32_t* PhysicalMEM,  FVM_IDT_HANDLER_t* FVM_IDTR)
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
				printf("R12 [%d]\n", CPU_regs->r12);
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
			default:
				printf("\n>>>>>>Emulator Halted by unknown opcode: [0x%X] R11: [0x%X]. Shutting Down....",PhysicalMEM[CPU_regs->r11], CPU_regs->r11);
				CPU_regs->ON = 0x0000;
				FVM_EXIT(FVM_PROGRAM_ERR);
		}
			return;
	}	
