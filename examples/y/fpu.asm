include 'a32.inc'
_start:
PUSH R0
JMPF MainClass.Main
MainClass.Main:
JMPF @f
include "console.lib"
@@:


PUSH MainClass.sin30
CALLF Console.WriteLine

PUSH 30.0

F_SINX


POP R1

VM_CALL 4

PUSH MainClass.cos30
CALLF Console.WriteLine

PUSH 30.0


F_COSX


POP R1

VM_CALL 4

VM_EXIT


_end_start:
_data:

MainClass.sin30: db 'sin(30r) =  ', 0
MainClass.cos30: db 'sin(30r) =   cos(30r) =  ', 0
_end_data:
_bss:
_end_bss: