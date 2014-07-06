include 'a32.inc'
_start:
PUSH R0
JMPF MainClass.Main
JMPF @f
include "console.inc"
@@:
MainClass.Main:


LOAD_R0 MainClass.Cool

PUSH MainClass.crapint
CALLF MainClass.Cool

PUSH MainClass.string1
CALLF Console.WriteLine

PUSH R0
LOAD_R0 MainClass.crapint
LOAD_REG_DWORD R1
POP R0

PUSH Mainclass.string1
CALLF MainClass.shit

VM_DEBUG


VM_EXIT


MainClass.Cool:


VM_EXIT


MainClass.shit:


LOAD_FROM_SP3


RETF


_end_start:
_data:

MainClass.string1: db 'Hello, World ', 0x0A, '', 0
MainClass.crapint: dd 203932
_end_data:
_bss:
_end_bss: