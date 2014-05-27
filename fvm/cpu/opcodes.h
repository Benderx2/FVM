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
#define CALLX 0x0005
//! RETX - Return to Address X
#define RETX 0x0006
//! LD12 - Load Stack Pointer 
#define FVM_LD12 0x0007
//! PUSH - Push to stack
#define FVM_PUSH 0x0008
//! POP1 - Pop something to stack into R1
#define FVM_POP1 0x0009
//! DEBUG - halt and print cpu status
#define FVM_DEBUG 0x000A
#endif

