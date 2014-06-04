//! OpCodes for FVM
#ifndef __OPCODES_H
#define __OPCODES_H
//! Define Opcodes
#define FVM_SLP 0x0000
//! EXT - Exit 
#define FVM_EXT 0x00FF
//! LD0 - Load a R0
#define FVM_LD0 0x0001
//! FCALL - FVM Call - Call a Virtual Machine Specific Function
#define FVM_FCALL 0x0002
//! LD1 - Load something into R1
#define FVM_LD1 0x0003
//! JTX - Jump to Address X
#define FVM_JTX 0x0004
//! Call Address X
//! RETX - Return to Address X
#define FVM_RET 0x0006
//! LD12 - Load Stack Pointer 
#define FVM_LD12 0x0007
//! PUSH - Push to stack
#define FVM_PUSH 0x0008
//! POP1 - Pop something to stack into reg
#define FVM_POPR 0x0009
//! DEBUG - halt and print cpu status
#define FVM_DEBUG 0x000A
//! LD1FA0 - Load R0 from address of FA1
#define FVM_LD1FA0 0x000B
// Call from address in R2
#define FVM_CALL 0x000C
//! LD2 - Load R2 - Address Register
#define FVM_LD2 0x000D
//! CMPV - Compare Register with value
#define FVM_CMPV 0x000E
//! JEX - Jump if Equal to address X
#define FVM_JEX 0x000F
//! JGX - Jump if Greater to address X
#define FVM_JGX 0x0010
//! JLX - Jump if lesser to address X
#define FVM_JLX 0x0011
//! ST1TA0 - Store R0 to address of R0
#define FVM_ST1TA0 0x0012
//! INT - Interrupt the processor
#define FVM_INT 0x0013
// LITH - Load Interrupt Handler
#define FVM_LITH 0x0014
// IRETX - Return from interrupt
#define FVM_IRETX 0x00015
// LD3 - Load R3
#define FVM_LD3 0x00016
// LD4 - Load R4
#define FVM_LD4 0x00017
// LD5 - Load R5
#define FVM_LD5 0x00018
// INCR - Increment Register
#define FVM_INCR 0x0019
// DECR - Decrement Register
#define FVM_DECR 0x001A
#endif

