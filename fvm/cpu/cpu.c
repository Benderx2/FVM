#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fvm/native/native.h>
#include <fvm/devices/fgx.h>
#include <fvm/tweaks.h>
#include <fvm/version.h>
#include <fvm/cpu/opcodes.h>
#include <fvm/cpu/registers.h>
#include <fvm/cpu/cpu.h>
#include <fvm/cpu/ports.h>
#include <fvm/fpu/fpu.h>
#include <fvm/cpu/mem/vmm.h>
#include <fvm/fcall/fcall.h>
#include <fvm/cpu/idt.h>
#include <fvm/error.h>
#include <fvm/gc/objects.h>
#include <fvm/thread/thread.h>
#include <fvm/sdl.h>
extern int total_mem;
uint8_t* byteptr;
uint32_t* dwordptr;
union tempuni {
	int32_t a;
	float b;
};
int32_t save_r12 = -1;
void emulate_FVM_instruction(FVM_REGISTERS_t* CPU_regs, FVM_REGISTERS_t* CPU2_regs, FVM_CPU_STATE_t* NewCPU_state, FFLAGS_t* CPU_Flags, FVM_PORT_t* IOADDRSPACE, int32_t* Memory,  FVM_IDT_HANDLER_t* FVM_IDTR, V_TABLE_t* vtable)
{
	UNUSED(NewCPU_state);
	FVM_BYTE_t* temp;
	// Refresh FGX video device.
	//FGX_refresh(IOADDRSPACE);	
	switch(Memory[CPU_regs->IP])
		{
			//! Sleep
			//! slp
			case FVM_SLP:
				//! Increment IP
				CPU_regs->IP++;
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
				temp  = &CPU_regs->r0;
				goto _load_instruction;	
			case FVM_LD1:
				temp = &CPU_regs->r1;
				goto _load_instruction;
			case FVM_LD2:
				temp = &CPU_regs->r2;
				goto _load_instruction;
			case FVM_LD3:
				temp = &CPU_regs->r3;
				goto _load_instruction;
			case FVM_LD4:
				temp = &CPU_regs->r4;			
				goto _load_instruction;
			case FVM_LD5:
				temp = &CPU_regs->r5;
				goto _load_instruction;
			case FVM_LD12:
				temp = &CPU_regs->r12;
			_load_instruction:
				switch(Memory[CPU_regs->IP+1])
				{
					case OPCODE_R0:
						*temp = CPU_regs->r0;
						break;
					case OPCODE_R1:
						*temp = CPU_regs->r1;
						break;
					case OPCODE_R2:
						*temp = CPU_regs->r2;
						break;
					case OPCODE_R3:
						*temp = CPU_regs->r3;
						break;
					case OPCODE_R4:
						*temp = CPU_regs->r4;
						break;
					case OPCODE_R5:
						*temp = CPU_regs->r5;
						break;
					case OPCODE_R12:
						*temp = CPU_regs->r12;
						break;
					default:
						*temp = Memory[CPU_regs->IP+1];
						break;
				}
				CPU_regs->IP += 2;
				break;
			//! LD1 Load R1
			//! ld1 value
			/* PUSH -- Push to the stack pointer */
			case FVM_PUSH:
				switch(Memory[CPU_regs->IP+1])
				{
					int32_t pushval;
					case OPCODE_R0:	
							pushval = CPU_regs->r0;
							goto _push_instruction;
					case OPCODE_R1:
							pushval = CPU_regs->r1;
							goto _push_instruction;
					case OPCODE_R2:
							pushval = CPU_regs->r2;
							goto _push_instruction;
					case OPCODE_R3:
							pushval = CPU_regs->r3;
							goto _push_instruction;
					case OPCODE_R4:
							pushval = CPU_regs->r4;
							goto _push_instruction;
					case OPCODE_R5:
							pushval = CPU_regs->r5;
							goto _push_instruction;
					case OPCODE_R12:	
							pushval = CPU_regs->r12;
							goto _push_instruction;
					default:
							pushval = Memory[CPU_regs->IP+1];
					_push_instruction:
							Memory[CPU_regs->r12] = pushval;
							CPU_regs->r12--;
							StackCount++;
							break;
				}
				CPU_regs->IP += 2;
				break;					//if (StackCount >= NewCPU_state->stack_limit)
				//{
				//	printf("\nR12 : [%X]", CPU_regs->r12);
				//	printf("\n>>>>>>Stack F**K Up. Exitting Emulator\n");
				//	FVM_EXIT(FVM_STACK_ERR);
				//}
				/* Pop out something from the stack into Reg */
			case FVM_POPR:
				if (Memory[CPU_regs->IP+1] == OPCODE_R0)	
				{
						CPU_regs->r0 = Memory[CPU_regs->r12+1];
				}
				else if (Memory[CPU_regs->IP+1] == OPCODE_R1)
				{
						CPU_regs->r1 = Memory[CPU_regs->r12+1];
				}
				else if (Memory[CPU_regs->IP+1] == OPCODE_R2)
				{
					CPU_regs->r2 = Memory[CPU_regs->r12+1];
				}	
				else if (Memory[CPU_regs->IP+1] == OPCODE_R3)
				{
					CPU_regs->r3 = Memory[CPU_regs->r12+1];
				}
				else if (Memory[CPU_regs->IP+1] == OPCODE_R4)
				{
					CPU_regs->r4 = Memory[CPU_regs->r12+1];
				}
				else if (Memory[CPU_regs->IP+1] == OPCODE_R5)
				{
					CPU_regs->r5 = Memory[CPU_regs->r12+1];
				}
				else if (Memory[CPU_regs->IP+1] == OPCODE_R12)
				{
					CPU_regs->r12 = Memory[CPU_regs->r12+1];
				}
						CPU_regs->r12++;
						StackCount--;
				if (StackCount < 0)
				{
					printf("\n>>>>>F**K UP: STACK COUNT IS UNDER ZERO (0) : [%X] R12 : [%X]\n", StackCount, CPU_regs->r12);
				}
				CPU_regs->IP += 2;
				break;
			//! FCALL - Call the operating system
			//! fcall call_number
			case FVM_FCALL:
				CPU_regs->IP = CPU_regs->IP;
				byteptr = (uint8_t*)Memory;
				int a = fcall(Memory[CPU_regs->IP+1], CPU_regs->r1, CPU_regs->r0, CPU_regs->r2, byteptr);
				if (a == -2)
				{
					CPU_regs->r1 = 0;
				}
				else if (a == FCALL_READ)
				{
					CPU_regs->r1 = 0;
					CPU_regs->r1 = keycode;
				}
				CPU_regs->IP += 2;
				break;
			//! JTX - Jump to Address X
			//! jtx address
			case FVM_JTX:
				CPU_regs->IP = Memory[CPU_regs->IP+1] / 4;
				break;
			case FVM_DEBUG:
				printf("\033[31m");
				printf("\n>>>>>>DEBUG Instruction OPCODE:{%X} Executed, Will print CPU status: \n>R0 : [%X]\n>R1 : [%X]\n>R2 : [%X]\n>R3 : [%X]\n>R4 : [%X]\n>R5 : [%X]\n>RX : [%X]\n>SP : [%X]\n>IP : [%X]\nEF : [%X]\nGF : [%X]\nLF : [%X]\n", FVM_DEBUG, CPU_regs->r0, CPU_regs->r1, CPU_regs->r2, CPU_regs->r3, CPU_regs->r4, CPU_regs->r5, CPU_regs->r17, CPU_regs->r12, CPU_regs->IP, CPU_Flags->E, CPU_Flags->G, CPU_Flags->L);
				//printf("Memory Contents: \n");
				//uint8_t* tmp = (uint8_t*)Memory;
				//uint32_t i = 0;
				//for (i = 0; i < total_mem; ++i)
				//{
				//	printf(" %c", tmp[i]);
				//} 
				printf("\033[0m");
				CPU_regs->IP++;
				break;
			/* LD1FA0 - Load R1 from address of R0, Loads a BYTE from address R0, and increments R0 */
			case FVM_LD1FA0:
				CPU_regs->IP = CPU_regs->IP;
				uint8_t* tmp2 = (uint8_t*)Memory;
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
				CPU_regs->IP++;
				CPU_regs->r0++;
				break;
			/* Jumps to a procedure whose address is in R2 */
			case FVM_CALL:
				CPU_regs->IP = CPU_regs->IP;
				uint32_t returnaddress = CPU_regs->IP + 2;
				Memory[CPU_regs->r12] = returnaddress;
				CPU_regs->IP = Memory[CPU_regs->IP+1] / 4;
				CPU_regs->r12--;
				save_r12 = CPU_regs->r12;
				StackCount++;
				//printf("\nR12: [%X]", CPU_regs->r12);
				//CPU_regs->r17 = CPU_regs->IP + 2;
				//CPU_regs->IP = Memory[CPU_regs->IP+1] / 4;
				break;
			/* Returns from a procedure done by FVM_CALL*/
			case FVM_RET:
				//CPU_regs->IP = CPU_regs->r17;
				//CPU_regs->r17 = 0;
				save_r12 = -1;
				CPU_regs->IP = Memory[CPU_regs->r12+1];
				CPU_regs->r12++;
				///printf("\nR12: [%X]", CPU_regs->r12);
				StackCount--;
				break;
			case FVM_LEAVE:
				CPU_regs->IP++;
				if(save_r12 == -1)
				{
					break;
				}
				else {
					CPU_regs->r12 = save_r12;
					break;
				}
				break;
			/* CMPR - Compare Register with value */
			case FVM_CMPV:
				CPU_regs->IP = CPU_regs->IP;
				int32_t value = Memory[CPU_regs->IP+1+1];
				int32_t EVAL1 = Memory[CPU_regs->IP+1];
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
				CPU_regs->IP += 3;
				break;
			/* JEX - Jump if Equal Flag is SET */
			case FVM_JEX:
					if(CPU_Flags->E == 1)
					{
						CPU_regs->IP = Memory[CPU_regs->IP+1] / 4;
						break;
					}
					else {
						CPU_regs->IP += 2;
						break;
					}
			/* JGX - Jump if Greater than flag is set */
			case FVM_JGX:
					if (CPU_Flags->G == 1)
					{
						CPU_regs->IP = Memory[CPU_regs->IP+1] / 4;
						break;
					}
					else {
						CPU_regs->IP += 2;
						break;
					}
			/* JLX - Jump if lesser than flag is set */
			case FVM_JLX:
					if (CPU_Flags->L == 1 && CPU_Flags->VMM == false)
					{
						CPU_regs->IP = Memory[CPU_regs->IP+1] / 4;
						break;
					}
					else if(CPU_Flags->L == 1 && CPU_Flags->VMM == true)
					{
						CPU_regs->IP = vmm_virtual_to_physical(vtable, Memory[CPU_regs->IP+1]) / 4;
						if(CPU_regs->IP == -1)
						{
							printf("V_FAULT()\n");
							FVM_EXIT(FVM_PROGRAM_ERR);
						}
					}
					else {
						CPU_regs->IP += 2;
						break;
					}
			/* ST1TA0 - Store R1 to adddress of R0 (BYTE!) */
			case FVM_ST1TA0:
				CPU_regs->IP = CPU_regs->IP;
				uint8_t* tmp3 = (uint8_t*)Memory;
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
					CPU_regs->IP++;
					CPU_regs->r0++;
				break;
			/* Interrupt - Interrupt the processor */
			case FVM_INT:
				CPU_regs->IP = CPU_regs->IP;
				uint32_t returnaddress1 = CPU_regs->IP + 2;
				Memory[CPU_regs->r12] = returnaddress1;
				CPU_regs->r12--;
				StackCount++;
				uint32_t inum = Memory[CPU_regs->IP+1];
				CPU_regs->IP = FVM_IDTR[inum].address;
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
				CPU_regs->IP++;
				break;
			/* IRETX - Return from interrupt */
			case FVM_IRETX:
				CPU_regs->IP = Memory[CPU_regs->r12+1];
				CPU_regs->r12++;
				StackCount--;
				break;
			/* INCR - Increment Reigster */
			case FVM_INCR:
				switch(Memory[CPU_regs->IP+1])
				{
					case OPCODE_R0:
						CPU_regs->r0++;
						break;
					case OPCODE_R1:
						CPU_regs->r1++;
						break;		
					case OPCODE_R2:
						CPU_regs->r2++;
						break;	
					case OPCODE_R3:
						CPU_regs->r3++;
						break;
					case OPCODE_R4:
						CPU_regs->r4++;
						break;	
					case OPCODE_R5:
						CPU_regs->r5++;
						break;	
					case OPCODE_R12:
						CPU_regs->r12++;
						break;
				}
				CPU_regs->IP += 2;
				break;
			/* DECR - Decrement Register */
			case FVM_DECR:
				switch(Memory[CPU_regs->IP+1])
				{
					case OPCODE_R0:
						CPU_regs->r0--;
						break;
					case OPCODE_R1:
						CPU_regs->r1--;
						break;		
					case OPCODE_R2:
						CPU_regs->r2--;
						break;	
					case OPCODE_R3:
						CPU_regs->r3--;
						break;
					case OPCODE_R4:
						CPU_regs->r4--;
						break;	
					case OPCODE_R5:
						CPU_regs->r5--;
						break;	
					case OPCODE_R12:
						CPU_regs->r12--;
						break;
				}
				CPU_regs->IP += 2;
				break;
			// Grab a DWORD from port
			case FVM_IN0:
				CPU_regs->r0 = IOADDRSPACE[Memory[CPU_regs->IP+1]].out;
				CPU_regs->IP += 2;
				break;
			/* Send a DWORD to port */
			case FVM_OUT0:
				IOADDRSPACE[Memory[CPU_regs->IP+1]].in = CPU_regs->r0;
				CPU_regs->IP += 2;
				break;
			case FVM_XOR:
				CPU_regs->IP = CPU_regs->IP;
				int32_t XOR_VAL2;
				// XOR is done only on registers
				// Get the second operand first, as the first will be the destination.
				if(Memory[CPU_regs->IP+1+1] == OPCODE_R0)
				{
					XOR_VAL2 = CPU_regs->r0;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R1)
				{
					XOR_VAL2 = CPU_regs->r1;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R2)
				{
					XOR_VAL2 = CPU_regs->r2;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R3)
				{
					XOR_VAL2 = CPU_regs->r3;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R4)
				{
					XOR_VAL2 = CPU_regs->r4;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R5)
				{
					XOR_VAL2 = CPU_regs->r5;
				}
				else {
					XOR_VAL2 = Memory[CPU_regs->IP+1+1];
				}
				// Get the first operand now and XOR() it with the second one.
				if(Memory[CPU_regs->IP+1] == OPCODE_R0)
				{
					CPU_regs->r0 = CPU_regs->r0 ^ XOR_VAL2;
					printf("XOR_VAL2: %X", XOR_VAL2);
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R1)
				{
					CPU_regs->r1 = CPU_regs->r1 ^ XOR_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R2)
				{
					CPU_regs->r2 = CPU_regs->r2 ^ XOR_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R3)
				{
					CPU_regs->r3 = CPU_regs->r3 ^ XOR_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R4)
				{
					CPU_regs->r4 = CPU_regs->r4 ^ XOR_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R5)
				{
					CPU_regs->r5 = CPU_regs->r5 ^ XOR_VAL2;
				}
				else {
					printf("Invalid XOR(), undefined behaviour");
					CPU_regs->IP += 3;
					break;
				}
				CPU_regs->IP += 3;
				break;
			case FVM_MUL:
				if(Memory[CPU_regs->IP+1] == OPCODE_R1)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r1;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R2)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R3)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r3;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R4)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r4;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R5)
				{
					CPU_regs->r0 = CPU_regs->r0 * CPU_regs->r5;
				}
				else {
					CPU_regs->r0 = CPU_regs->r0 * Memory[CPU_regs->IP+1];
				}
				CPU_regs->IP += 2;
				break;
			case FVM_DIV:
				if(Memory[CPU_regs->IP+1] == OPCODE_R1)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r1;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R2)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R3)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r3;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R4)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r4;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R5)
				{
					CPU_regs->r0 = CPU_regs->r0 / CPU_regs->r5;
				}
				else {
					CPU_regs->r0 = CPU_regs->r0 * Memory[CPU_regs->IP+1];
				}
				CPU_regs->IP += 2;
				break;
			// Bitwise AND
			case FVM_AND:
				CPU_regs->IP = CPU_regs->IP;
				int32_t AND_VAL2;
				if(Memory[CPU_regs->IP+1+1] == OPCODE_R0)
				{
					AND_VAL2 = CPU_regs->r0;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R1)
				{
					AND_VAL2 = CPU_regs->r1;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R2)
				{
					AND_VAL2 = CPU_regs->r2;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R3)
				{
					AND_VAL2 = CPU_regs->r3;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R4)
				{
					AND_VAL2 = CPU_regs->r4;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R5)
				{
					AND_VAL2 = CPU_regs->r5;
				}
				else {
					AND_VAL2 =  Memory[CPU_regs->IP+1+1];
				}
				// Now set the operands appropriately
				if(Memory[CPU_regs->IP+1] == OPCODE_R0)
				{
					CPU_regs->r0 = CPU_regs->r0 & AND_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R1)
				{
					CPU_regs->r1 = CPU_regs->r1 & AND_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R2)
				{
					CPU_regs->r2 = CPU_regs->r2 & AND_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R3)
				{
					CPU_regs->r3 = CPU_regs->r3 & AND_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R4)
				{
					CPU_regs->r4 = CPU_regs->r4 & AND_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R5)
				{
					CPU_regs->r5 = CPU_regs->r5 & AND_VAL2;
				}
				CPU_regs->IP += 3;		
				break;
			// VMMINIT - Intialize Virtual Memory
			case FVM_VMMINIT:
				CPU_Flags->VMM = true;
				CPU_regs->IP++;
			// VMMQUIT - Deinitialize Virtual memory
			case FVM_VMMQUIT:
				CPU_Flags->VMM = false;
				CPU_regs->IP++;
			// STD - Store Register (DWORD) in addressof(R0)
			case FVM_STD:
				CPU_regs->IP = CPU_regs->IP;
				uint8_t* tmp4 = (uint8_t*)Memory;
				int32_t saver0 = CPU_regs->r0;
				if(CPU_Flags->VMM == true)
				{
					CPU_regs->r0 = vmm_virtual_to_physical(vtable, CPU_regs->r0);
				}
				uint32_t* dummy1 = (uint32_t*)&tmp4[CPU_regs->r0];
				if(Memory[CPU_regs->IP+1] == OPCODE_R0)
				{
					*dummy1 = CPU_regs->r0;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R2)
				{
					*dummy1 = CPU_regs->r2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R3)
				{
					*dummy1 = CPU_regs->r3;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R4)
				{
					*dummy1 = CPU_regs->r4; 
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R5)
				{
					*dummy1 = CPU_regs->r5;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R12)
				{
					*dummy1 = CPU_regs->r12;
				}
				CPU_regs->r0 = saver0;
				CPU_regs->IP += 2;
				break;
			// LDD - Load Register DWORD
			case FVM_LDD:
				CPU_regs->IP = CPU_regs->IP;
				uint8_t* tmp5 = (uint8_t*)Memory;
				int32_t saver0_1 = CPU_regs->r0;
				if(CPU_Flags->VMM == true)
				{	
					CPU_regs->r0 = vmm_virtual_to_physical(vtable, CPU_regs->r0);
				}
				uint32_t* dummy2 = (uint32_t*)&tmp5[CPU_regs->r0];
				if(Memory[CPU_regs->IP+1] == OPCODE_R0)
				{
					CPU_regs->r0=*dummy2;
					printf("R0 = %d ", CPU_regs->r0);	
					printf("dummy2 = %d", *dummy2);
					CPU_regs->IP += 2;
					break;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R2)
				{
					  CPU_regs->r2=*dummy2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R3)
				{
					 CPU_regs->r3=*dummy2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R4)
				{
					  CPU_regs->r4=*dummy2; 
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R5)
				{
					 CPU_regs->r5= *dummy2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R12)
				{
					 CPU_regs->r12=*dummy2;
				}
				CPU_regs->r0 = saver0_1;
				CPU_regs->IP += 2;
				break;
			// ADD - Add two registers, or a constant with a register
			case FVM_ADD:
				CPU_regs->IP = CPU_regs->IP;
				int32_t ADD_VAL2;
				if(Memory[CPU_regs->IP+1+1] == OPCODE_R0)
				{
					 ADD_VAL2 = CPU_regs->r0;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R1)
				{
					 ADD_VAL2 = CPU_regs->r1;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R2)
				{
					 ADD_VAL2 = CPU_regs->r2;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R3)
				{
					 ADD_VAL2 = CPU_regs->r3;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R4)
				{
					 ADD_VAL2 = CPU_regs->r4;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R5)
				{
					 ADD_VAL2 = CPU_regs->r5;
				}
				else {
					 ADD_VAL2 =  Memory[CPU_regs->IP+1+1];
				}
				// Now set the operands appropriately
				if(Memory[CPU_regs->IP+1] == OPCODE_R0)
				{
					CPU_regs->r0 = CPU_regs->r0 +  ADD_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R1)
				{
					CPU_regs->r1 = CPU_regs->r1 +  ADD_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R2)
				{
					CPU_regs->r2 = CPU_regs->r2 +  ADD_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R3)
				{
					CPU_regs->r3 = CPU_regs->r3 +  ADD_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R4)
				{
					CPU_regs->r4 = CPU_regs->r4 +  ADD_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R5)
				{
					CPU_regs->r5 = CPU_regs->r5 +  ADD_VAL2;
				}
				printf(">>>>>>>LOG AND VAL 2 %d\n", ADD_VAL2);
				CPU_regs->IP += 3;
				break;
			// Subtract 2 registers
			case FVM_SUB:
				CPU_regs->IP = CPU_regs->IP;
				int32_t SUB_VAL2;
				if(Memory[CPU_regs->IP+1+1] == OPCODE_R0)
				{
					 SUB_VAL2 = CPU_regs->r0;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R1)
				{
					 SUB_VAL2 = CPU_regs->r1;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R2)
				{
					 SUB_VAL2 = CPU_regs->r2;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R3)
				{
					 SUB_VAL2 = CPU_regs->r3;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R4)
				{
					 SUB_VAL2 = CPU_regs->r4;
				}
				else if(Memory[CPU_regs->IP+1+1] == OPCODE_R5)
				{
					 SUB_VAL2 = CPU_regs->r5;
				}
				else {
					 SUB_VAL2 =  Memory[CPU_regs->IP+1+1];
				}
				// Now set the operands appropriately
				if(Memory[CPU_regs->IP+1] == OPCODE_R0)
				{
					CPU_regs->r0 = CPU_regs->r0 -  SUB_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R1)
				{
					CPU_regs->r1 = CPU_regs->r1 - SUB_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R2)
				{
					CPU_regs->r2 = CPU_regs->r2 - SUB_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R3)
				{
					CPU_regs->r3 = CPU_regs->r3 - SUB_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R4)
				{
					CPU_regs->r4 = CPU_regs->r4 - SUB_VAL2;
				}
				else if(Memory[CPU_regs->IP+1] == OPCODE_R5)
				{
					CPU_regs->r5 = CPU_regs->r5 - SUB_VAL2;
				}
				CPU_regs->IP += 3;
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
						vtable = (V_TABLE_t*)(Memory + Memory[CPU_regs->IP+1]);
					}
					CPU_regs->r12 += 2;
					break;
			// LDSP - Load R1 from Stack Pointer Offset (i.e. LDSP 1 will load R1 from the first 4-bytes down the stack, LDSP 2 will load it from 8-bytes down the stack)
			case FVM_LDSP:
					CPU_regs->r1 = Memory[CPU_regs->r12 + Memory[CPU_regs->IP+1]];
					CPU_regs->IP += 2;
					break;
			/** SUBLEQ - Subtract and store and jump if equal. **/
		        case FVM_SUBLEQ: 	 
					CPU_regs->IP++;
					byteptr = (uint8_t*)Memory;
					byteptr[(Memory[CPU_regs->IP+1])] = byteptr[(Memory[CPU_regs->IP+1])] - byteptr[(Memory[CPU_regs->IP])];  
					printf("SUBLEQ: Result of Operation: %u, operand a : %u\n", byteptr[(Memory[CPU_regs->IP+1])], byteptr[(Memory[CPU_regs->IP])]);
					int8_t temporary = byteptr[(Memory[CPU_regs->IP+1])];
					if(temporary <= 0)
					{
						CPU_regs->IP = Memory[CPU_regs->IP+2] / 4;
					}
					else {
						CPU_regs->IP += 3;
					}
					break;
			/** Initialize Core 2 with IP. **/
			case FVM_INIT_MP:
				CPU_regs->r17 = 1;
				CPU2_regs->IP = Memory[CPU_regs->IP+1] / 4;	
				CPU_regs->IP += 2;
				break;
			/** Deintialize Core 2 **/
			case FVM_DEINIT_MP:
				CPU_regs->r17 = 0;
				CPU_regs->IP++;
				break;
			case FVM_NATIVE_CALL:
				// Call a native procedure
				CPU_regs->IP++;
				char* libname = (char*)Memory + Memory[CPU_regs->IP];
				char* functionname = (char*)Memory + Memory[CPU_regs->IP+1];
				uint32_t* arg = (uint32_t*)Memory + Memory[CPU_regs->IP+2];
				void* handle = returnhandle(libname);
				if(handle == NULL){
					/** try loading it then **/
					printf("Loading library : %s\n", libname);
					if(handle == NULL) {
						handle = load_native_library(libname);
						if(handle == NULL){
						// Not found then :P
						printf("FATAL: NATIVE_CALL, Library Not found, %s, Requested procedure, %s.\n", libname, functionname);
						}
						CPU_regs->r0 = native_call(functionname, handle, (void*)arg);
					}
				}
				else {
					CPU_regs->r0 = native_call(functionname, handle, (void*)arg);
				}
				CPU_regs->IP += 3;
				break;
			
			/** Memory Management **/
			case CREAT_THREAD:
				CPU_regs->r0 = (uint32_t)create_thread(Memory[CPU_regs->IP+1] / 4, Memory[CPU_regs->IP+2] / 4);
				CPU_regs->IP += 3;
				break;
			case THREAD_EXIT:
				destroy_thread(CPU_regs->no);
				CPU_regs->IP++;
				break;
			case OBJ_CREAT:
				 CPU_regs->IP++;
				 Object* objtemp = VM_CreateObject(Memory[CPU_regs->IP] /** Type **/, Memory[CPU_regs->IP+1] /** Value/Address **/);
				 Memory[CPU_regs->r12] = objtemp->index;
				 CPU_regs->IP++;
				 break;
			case OBJ_STORE:
				CPU_regs->IP++;
				break;
			/** Instructions used by relocatable code **/
			case FVM_RELOC_JMP:
				CPU_regs->IP = CPU_regs->thread_local_storage + (Memory[CPU_regs->IP+1] / 4);
				break;
			/** Load from relative address in R0 **/
			case FVM_RELOC_STD:
				CPU_regs->IP = CPU_regs->IP;
				uint8_t* tmp6 = (uint8_t*)Memory;
				switch(Memory[CPU_regs->IP+1])
				{
					case OPCODE_R0:
						tmp6[CPU_regs->r0 + (CPU_regs->thread_local_storage * 4)] = CPU_regs->r0;
					case OPCODE_R1:
						tmp6[CPU_regs->r0 + (CPU_regs->thread_local_storage * 4)] = CPU_regs->r1;
					case OPCODE_R2:
						tmp6[CPU_regs->r0 + (CPU_regs->thread_local_storage * 4)] = CPU_regs->r2;
					case OPCODE_R3:
						tmp6[CPU_regs->r0 + (CPU_regs->thread_local_storage * 4)] = CPU_regs->r3;
					case OPCODE_R4:
						tmp6[CPU_regs->r0 + (CPU_regs->thread_local_storage * 4)] = CPU_regs->r4;
					case OPCODE_R5:
						tmp6[CPU_regs->r0 + (CPU_regs->thread_local_storage * 4)] = CPU_regs->r5;
					case OPCODE_R12:
						tmp6[CPU_regs->r0 + (CPU_regs->thread_local_storage * 4)] = CPU_regs->r12;
					default:
						tmp6[CPU_regs->r0 + (CPU_regs->thread_local_storage * 4)] = Memory[CPU_regs->IP+1];
						
				}
				CPU_regs->IP += 2;
				break;
			case FVM_RELOC_LDD:
				CPU_regs->IP = CPU_regs->IP;
				uint8_t* tmp7 = (uint8_t*)Memory;
				switch(Memory[CPU_regs->IP+1])
				{
					case OPCODE_R0:
						CPU_regs->r1 = tmp7[CPU_regs->r0 + (CPU_regs->thread_local_storage * 4)];
					case OPCODE_R1:
						CPU_regs->r1 = tmp7[CPU_regs->r1 + (CPU_regs->thread_local_storage * 4)];
					case OPCODE_R2:
						CPU_regs->r1 = tmp7[CPU_regs->r2 + (CPU_regs->thread_local_storage * 4)];
					case OPCODE_R3:
						CPU_regs->r1 = tmp7[CPU_regs->r3 + (CPU_regs->thread_local_storage * 4)];
					case OPCODE_R4:
						CPU_regs->r1 = tmp7[CPU_regs->r4 + (CPU_regs->thread_local_storage *   4)];	
					case OPCODE_R5:
						CPU_regs->r1 = tmp7[CPU_regs->r5 + (CPU_regs->thread_local_storage * 4)];	
					case OPCODE_R12:
						CPU_regs->r1 = tmp7[CPU_regs->r12 + (CPU_regs->thread_local_storage * 4)];
					default:
						CPU_regs->r1 = tmp7[Memory[CPU_regs->IP+1] + (CPU_regs->thread_local_storage * 4)];
				}
				CPU_regs->IP += 2;
				break;	
			case FVM_RELOC_JMPFE:
				if(CPU_Flags->E == 1)
				{	
					CPU_regs->IP = (CPU_regs->thread_local_storage + (Memory[CPU_regs->IP+1] / 4));
					break;
				}
				CPU_regs->IP += 2;
				break;
			case FVM_RELOC_JMPFL:
				if(CPU_Flags->L == 1)
				{	
					CPU_regs->IP = (CPU_regs->thread_local_storage + (Memory[CPU_regs->IP+1] / 4));
					break;
				}
				CPU_regs->IP += 2;
				break;
			case FVM_RELOC_JMPFG:
				if(CPU_Flags->G == 1)
				{	
					CPU_regs->IP = (CPU_regs->thread_local_storage + (Memory[CPU_regs->IP+1] / 4));
					break;
				}
				CPU_regs->IP += 2;
				break;
			case FVM_GETMEM:
				CPU_regs->r0 = total_mem;
				CPU_regs->IP++;
				break;
			case FVM_MEMCMP:
				CPU_Flags->E = true; // Is Equal.
				// Let's do a memory compare. R0 is the first block memory to compare, and R1 the second. 
				// The length is in R2.
				uint8_t* mem8aux = (uint8_t*)Memory;
				for(int i = 0; i < CPU_regs->r2; i++)
				{
					printf("R1 %c\n", mem8aux[CPU_regs->r1 + i]);
					printf("R0 %c\n", mem8aux[CPU_regs->r0 + i]);
					if(mem8aux[CPU_regs->r1 + i] == mem8aux[CPU_regs->r0 + i])	
					{
						// Keep goin'!
					}
					else {
						CPU_regs->r2 = i;
						CPU_Flags->E = false;
						break; 
					}
				}
				printf("E = %d\n", CPU_Flags->E);
				CPU_regs->IP++;
				break;
			/** FPU Functions **/
			case FPU_SIN:	
				CPU_regs->IP++;
				float result = do_sin_x(Memory[CPU_regs->r12+1]); /** Grab shit from stack **/
				printf("LOG>> FPU SIN() = %f of %u\n", result, Memory[CPU_regs->r12+1]);
				/** Push it! **/
				pushfloat(Memory, CPU_regs->r12, result);	
				CPU_regs->r12--;  /** Decrement the stack **/
				break;	
			case FPU_COS:
				CPU_regs->IP++;	
				float cosresult = do_cos_x(Memory[CPU_regs->r12+1]);
				printf("LOG>> FPU COS() = %f of %u\n", cosresult, Memory[CPU_regs->r12+1]);
				pushfloat(Memory, CPU_regs->r12, cosresult);
				CPU_regs->r12--;
				break;	
			case FPU_POW:
				CPU_regs->IP++;
				/** PUSH 3.0f PUSH 2.0f  F_POW == 3^2 = 9 **/
				float resultpow = do_pow_x(Memory[CPU_regs->r12+2], Memory[CPU_regs->r12+1]);
				pushfloat(Memory, CPU_regs->r12, resultpow);
				CPU_regs->r12--;
				break;
			case FPU_ABS:
				CPU_regs->IP++;
				pushfloat(Memory, CPU_regs->r12, do_abs_x(Memory[CPU_regs->r12+1]));
				CPU_regs->r12--;
				break;
			case FPU_FACT:
				pushfloat(Memory, CPU_regs->r12, do_fact_x(Memory[CPU_regs->r12+1]));
				printf("factorial of stuff: %f", *(float*)&Memory[CPU_regs->r12]);
				CPU_regs->IP++;
				// TODO: Stop acting like an asshole and do some stack checks before decrementing the stack pointer.
				// TODO(2):  Shut the fuck up and add stack checks everywhere!
				CPU_regs->r12--;
				break; 
			case FPU_ASIN:
				pushfloat(Memory, CPU_regs->r12, do_asin_x(Memory[CPU_regs->r12+1]));
				printf("asin of shit: %f\n", *(float*)&Memory[CPU_regs->r12]);
				goto arc_common_done;
			case FPU_ACOS:
				pushfloat(Memory, CPU_regs->r12, do_acos_x(Memory[CPU_regs->r12+1]));
				printf("acos of shit: %f\n", *(float*)&Memory[CPU_regs->r12]);
				goto arc_common_done;
			case FPU_ATAN:
				pushfloat(Memory, CPU_regs->r12, do_atan_x(Memory[CPU_regs->r12+1]));
				goto arc_common_done;
			case FPU_ADD:
				pushfloat(Memory, CPU_regs->r12, do_arithmetic_operation(Memory[CPU_regs->r12+2], Memory[CPU_regs->r12+1], FPU_ADD));
				goto _fpu_arith_common_done;
			case FPU_SUB:
				pushfloat(Memory, CPU_regs->r12, do_arithmetic_operation(Memory[CPU_regs->r12+2], Memory[CPU_regs->r12+1], FPU_SUB));
				goto _fpu_arith_common_done;
			case FPU_MUL:
				pushfloat(Memory, CPU_regs->r12, do_arithmetic_operation(Memory[CPU_regs->r12+2], Memory[CPU_regs->r12+1], FPU_MUL));
				goto _fpu_arith_common_done;
			case FPU_DIV:
				pushfloat(Memory, CPU_regs->r12, do_arithmetic_operation(Memory[CPU_regs->r12+2], Memory[CPU_regs->r12+1], FPU_DIV));
				goto _fpu_arith_common_done;
			_fpu_arith_common_done:
				CPU_regs->r12--;
				CPU_regs->IP++;
				break;			
			arc_common_done:
				CPU_regs->IP++;
				CPU_regs->r12--;
				break;
		default:
				printf("\n>>>>>>Emulator Halted by unknown opcode: [0x%X] IP: [0x%X]. Shutting Down...., Previous DWORD: [0x%X], Next DWORD : [0x%X]\n",Memory[CPU_regs->IP], CPU_regs->IP, Memory[CPU_regs->IP-1], Memory[CPU_regs->IP+1]);
				CPU_regs->ON = 0x0000;
				FVM_EXIT(FVM_PROGRAM_ERR);
		}
			return;
	}
