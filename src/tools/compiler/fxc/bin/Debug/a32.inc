; A32 - Include file for FVM A32 VM.
; For HLL Compilers.....
; Register marker definitions
define R0 -257
define R1 -258
define R2 -259
define R3 -261
define R4 -262
define R5 -263
define BP -264
define SP -260
define MUL_XY 0 
define DIV_XY 1
define SUB_XY 2
define ADD_XY 3
define SET_XY 4
org 0
align 4
use32
; Header
dd 0xC00C1E5
; Load address is 0
dd _start
; This executable's text section' is loaded at start. No need of anything else unless you want to RE-ORG.
dd _start
dd _end_start - _start
dd _data
dd _data
dd _end_data - _data
dd _bss
dd _end_bss - _bss
if defined STACK_SIZE 
	dd _end_bss + STACK_SIZE
else 
; Fall back to default stack size.
dd _end_bss + 200
end if
; Vendor String
db 'FVVENDOR'
; No classes required!
if defined CLASS_REQ
dd class_req
dd class_table
else 
dd 0
dd 0
end if
; No relocatable function table!
dd 0
; V_SLEEP - Processor Sleep
macro LOAD_R op1, op2 {
	dd 0x58
	dd op1 
	dd op2
}
macro OPERATE op1, op2, op3 {
	dd 0x59
	dd op1
	dd op2
	dd op3
}
macro V_SLEEP {
	dd 0x0
}
macro LEAVE {
	 dd 0x42
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
macro LOAD a, b {
	if a = R0
	LOAD_R0 b
	else if a = R1
	LOAD_R1 b
	else if a = R2
	LOAD_R2 b
	else if a = R3
	LOAD_R3 b
	else if a = R4
	LOAD_R4 b
	else if a = R5
	LOAD_R5 b
	end if
}
; Load Memory from second register to first
macro LOAD_M reg1, reg2
{
	dd 0x54
	dd reg1
	dd reg2
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
macro JMPF_Z ADDRESS
{
	dd 0x5F
	dd ADDRESS
}
; Jump if greater or equal
macro JMPF_GE l {
	JMPF_E l
	JMPF_G l
}
macro JMPF_LE l {
	JMPF_E l
	JMPF_L l
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
macro IN PORT
{	
	dd 0x1D
	dd PORT
}
; OUT_R0 - Send out R0 to port
macro OUT PORT
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
macro LSHIFT OP1, OP2
{
	dd 0x5C
	dd OP1
	dd OP2
}
macro RSHIFT OP1, OP2
{
	dd 0x5B
	dd OP1
	dd OP2
}
macro OR OP1, OP2
{
	dd 0x5A
	dd OP1
	dd OP2
}
macro DUP {
	dd 0x60
}
macro PUSHF {
	dd 0x5D
}
macro POPF {
	dd 0x5E
}
macro VM_EXIT
{
	dd 0xFF
}
macro ADDR op1, op2 {
	dd 0x27
	dd op1
	dd op2
}
macro SUBR op1, op2 {
	dd 0x28
	dd op1
	dd op2
}
macro LOAD_FROM_SP off
{
	dd 0x29
	dd off
}
macro LOAD_BP shit
{
	dd 0x30	
	dd shit
}
macro F_SINX {
	dd 0x031
}
macro F_COSX {
	dd 0x032
}
macro F_ABS {
	dd 0x34
}
macro F_POW {
	dd 0x033
}
macro F_SUB {
	dd 0x36
}
macro F_MUL {
	dd 0x37
}
macro F_DIV {
	dd 0CPU_regs-x38
}
macro F_ADD {
	dd 0x35
}
macro F_FACT {
	dd 0x0043
}
macro F_ASIN {
	dd 0x39
}
macro F_ACOS {
	dd 0x40
}
macro F_ATAN {
	dd 0x41
}
; PPU Stuff
macro PPU_WRITE {
	dd 0x55 
}
macro PPU_READ {
	dd 0x56
}
macro PPU_UPDATE {
	dd 0x57
}
macro CREATE_RELOCATABLE_LABEL address {
	JMPF address
}
macro SUBLEQ a, b, c {
	dd 0x0046
	dd a
	dd b
	dd c
}
macro MEMCMP {
	dd 0x53
}
macro MEMCPY {
	dd 0x61
}
macro DEINIT_MP {
	dd 0x48
}
macro INIT_MP ip {
	dd 0x47
	dd ip
}
macro DECLARE_NATIVE_LIB name {
	db name, 0
}
macro DECLARE_NATIVE_PROC name {
	db name, 0
}
macro DECLARE_STACK_SPACE no {
	times no db 0
}
macro NATIVE_CALL lib, name, arg {
	dd 0x49
	dd lib
	dd name
	dd arg
}
macro VM_CREATE_THREAD ip, stack {
	dd 0x004A
	dd ip 
	dd stack
}
macro THREAD_EXIT {
	dd 0x004B
}
macro RELOC_JMP addr {
	dd 0x004C
	dd addr
}
macro RELOC_JE addr {
	dd 0x004F
	dd addr
}
macro RELOC_JG addr {	
	dd 0x0050
	dd addr
}
macro RELOC_JL addr {
	dd 0x0051
	dd addr
}
macro RELOC_LDD reg {
	dd 0x004E
	dd reg
}
macro RELOC_STD reg {
	dd 0x004D
	dd reg
}
