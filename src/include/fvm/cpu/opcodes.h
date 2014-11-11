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
// Call 
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
// GPU PREFIX Another 4-byte GPU Instruction is next
#define FVM_GPU_PREFIX 0x001B
// OUT0 -- Send a DWORD to port
#define FVM_OUT0 0x001C
// IN0 -- Send a DWORD to port
#define FVM_IN0 0x001D
// XOR -- XOR Register, with register or immediate
#define FVM_XOR 0x001E
// AND - And with Register
#define FVM_AND 0x001F
// MUL - Multiply 
#define FVM_MUL 0x0020
// DIV - Divide
#define FVM_DIV 0x0021
// V_ENABLE - Enable Virtual Memory
#define FVM_VMMINIT 0x0022
// V_DISABLE - Disable Virtual Memory
#define FVM_VMMQUIT 0x0023
// STD - Store Register DWORD
#define FVM_STD 0x0024
// LDD - Load Register DWORD
#define FVM_LDD 0x0025
// FVM_V_LOAD - Load Virtual Table
#define FVM_V_LOAD 0x0026
// ADD - Add register and operand
#define FVM_ADD 0x0027
// SUB - Subtract Register and operand or vice versa
#define FVM_SUB 0x0028
// Load from stack
#define FVM_LDSP 0x0029
// LDBP - Load Base ptr
#define FVM_LDBP 0x0030
// FPU_SIN - Calculate sine of 32-bit float on stack
#define FPU_SIN 0x0031
// FPU_COS Calculate Cosine of 32-bit float on stack
#define FPU_COS 0x0032
// FPU_POW - Raise powers
#define FPU_POW 0x0033
// FPU ABS - Absolute Value
#define FPU_ABS 0x0034
// FPU_ADD - Add two floats
#define FPU_ADD 0x0035
// FPU SUB - Subtract floats
#define FPU_SUB 0x0036
// FPU MUL - Multiply floats
#define FPU_MUL 0x0037
// FPU DIV - Divide floats
#define FPU_DIV 0x0038
// F_ACOS - Calculate Arccosine
#define FPU_ACOS 0x0040
// F_ASIN - Calculate Arcsin
#define FPU_ASIN 0x0039
// ATAN - Arctan
#define FPU_ATAN 0x0041
// LEAVE - Clear stack space
#define FVM_LEAVE 0x0042
// F_FACT - Calculate factorial 
#define FPU_FACT 0x0043
// OBJ_CREAT - Create Object 
#define OBJ_CREAT 0x0044
// OBJ_STORE - Store Object
#define OBJ_STORE 0x0045
// FVM_SUBLEQ - SUbtract and Branch if LEss than or EQual
#define FVM_SUBLEQ 0x0046
// INIT_MP - Intialize cpu2 with IP.
#define FVM_INIT_MP 0x0047
// DEINIT_MP - Deinitialize cpu2
#define FVM_DEINIT_MP 0x0048
// NATIVE_CALL - Call native procedure
#define FVM_NATIVE_CALL 0x0049
// CREAT_THREAD - Create a new thread
#define CREAT_THREAD 0x0004A
// THREAD_EXIT - Exit current thread;
#define THREAD_EXIT 0x004B
// RELOC_JMP - Relative JMPF
#define FVM_RELOC_JMP 0x004C
// RELOC_STD - Relative Store
#define FVM_RELOC_STD 0x004D
// RELOC_LDD - Relative Load
#define FVM_RELOC_LDD 0x004E
// RELOC_JMP_F_E - Relative Jump if equal
#define FVM_RELOC_JMPFE 0x004F
// RELOC_JMP_F_G - Relative jump if greater
#define FVM_RELOC_JMPFG 0x0050
// RELOC_JMP_F_L - Relative jump if lesser
#define FVM_RELOC_JMPFL 0x0051
// FVM_GET_MEM - Get Total Memory in R1
#define FVM_GETMEM 0x0052
// MEM_CMP - Compare Memory blocks (R0, R1) with a specific length (R2)
#define FVM_MEMCMP 0x0053
// LOADM
#define FVM_LOADM 0x0054
#define FVM_WRITE_PPU 0x55
#define FVM_READ_PPU 0x56
#define FVM_UPDATE_PPU 0x57
#define FVM_LOADR 0x58
#define FVM_OPERATE 0x59
#define FVM_OR 0x5A
#define FVM_RSHIFT 0x5B
#define FVM_LSHIFT 0x5C
#define FVM_PUSHF 0x5D
#define FVM_POPF 0x5E
#define FVM_JMPFZ 0x5F
#define FVM_DUP 0x60
#define FVM_MEMCPY 0x61
#endif

