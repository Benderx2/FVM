; A32 - Include file for FVM A32 VM.
; For HLL Compilers.....
; Register marker definitions
define R0 -257
define R1 -258
define R2 -259
define R3 -261
define R4 -262
define R5 -262
define SP -260
; V_SLEEP - Processor Sleep
macro V_SLEEP {
	dd 0x0
}
; LOAD_R0 - Load Register R0
macro LOAD_R0 VALUE {	
	dd 0x01
	dd VALUE
}
; LOAD_R1 - Load Register R1
macro LOAD_R1 VALUE {
	dd 0x03
	dd VALUE
}
; LOAD_R2 - Load Register R2
macro LOAD_R2 VALUE {
	dd 0x0D
	dd VALUE
}
; LOAD_R3 - Load Register R3
macro LOAD_R3 VALUE
{
	dd 0x16
	dd VALUE
}
; LOAD_R4 - Load Register R4
macro LOAD_R4 VALUE 
{
	dd 0x17
	dd VALUE
}
; LOAD_R5 - Load Register R5
macro LOAD_R5 VALUE 
{
	dd 0x18
	dd VALUE
}
; LOAD_SP - Load Stack Pointer
macro LOAD_SP VALUE
{
	dd 0x07
	dd VALUE
}
; PUSH - Push a Value or Register to addressof(sp)
macro PUSH VALUE
{	
	dd 0x08
	dd VALUE
}
; POP - Pop a value from stack into register
macro POP VALUE
{
	dd 0x09
	dd VALUE
}
; VM_DEBUG - Output Register and VM Status to stdout
macro VM_DEBUG 
{
	dd 0x0A
}
; VM_CALL - Call VM Specfic Function
macro VM_CALL VALUE
{
	dd 0x02
	dd VALUE
}
; CALL - Push IP to stack, jump to procedure return back after RET (Address must be 4-byte aligned or UDB)
macro CALLF ADDRESS {
	dd 0x0C
	dd ADDRESS
}
; RETF - Return From Procedure 
macro RETF {
	dd 0x06
}
; JMPF - Jump to Procedure -- 4-byte alinged address or expect Undefined Behaviour
macro JMPF VALUE
{
	dd 0x04
	dd VALUE
}
; LOAD_BYTE - Load a Byte from addressof(R0) and store it in R1, and increment R0... similar to LODSB under x86
macro LOAD_BYTE 
{
	dd 0xB
}
; STORE_BYTE - Store a Byte to addressof(R0) which is in R1
macro STORE_BYTE
{
	dd 0x12
}
; LOAD_REGDWORD - Load a DWORD from addressof(R0) into specfied register
macro LOAD_REGDWORD REG
{
	dd 0x25
	dd REG
}
; STORE_REGDWORD - Store a DWORD from addressof(R0) from specfied register
macro STORE_REGDWORD REG
{
	dd 0x24
	dd REG
} 
; CMPR - Compare Register with immediate or value and sets E, G, L flags appropriately
macro CMPR VALUE1, VALUE2
{
	dd 0x0E
	dd VALUE1
	dd VALUE2
}
; JMPF_E - Jump to procedure if E is set.
macro JMPF_E ADDRESS
{
	dd 0x0F
	dd ADDRESS
}
; JMPF_G - Jump to procedure if E is set.
macro JMPF_G ADDRESS
{
	dd 0x10
	dd ADDRESS
}
; JMPF_L - Jump to procdeure if L is set.
macro JMPF_L ADDRESS 
{
	dd 0x11
	dd ADDRESS
}
; LOAD_INTERRUPT - R0 = Handler Address (4-byte alinged), R1 = Interrupt Number
macro LOAD_INTERRUPT
{
	dd 0x14
}
; INT - Cause a processor interrupt
macro INT VAL
{
	dd 0x13
	dd VAL
}
; IRETF - Return from an interrupt procedure
macro IRETF 
{
	dd 0x15
}
; IN_R0 - Grab value into R0 from port
macro IN_R0 PORT
{	
	dd 0x1D
	dd PORT
}
; OUT_R0 - Send out R0 to port
macro OUT_R0 PORT
{
	dd 0x1C
	dd PORT
}
; MUL - Multiply R0 with Register/Vaue and store the result in R0
macro MUL REG
{
	dd 0x20
	dd REG
}
; DIV - Divide R0 with Register/Vaue and store the result in R0
macro DIV REG
{
	dd 0x21
	dd REG
}
; INCR - Increment Register
macro INCR REG
{
	dd 0x19
	dd REG
}
; Decrement Register
macro DECR REG
{
	dd 0x1A
	dd REG
}
; Do an eXclusive OR on operands
macro XOR OP1, OP2
{
	dd 0x1E
	dd OP1
	dd OP2
}
; Do a bitwise AND on operands
macro AND OP1, OP2
{
	dd 0x1F
	dd OP1
	 dd OP2
}
macro VM_EXIT
{
	dd 0xFF
}


