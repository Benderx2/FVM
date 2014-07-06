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


POP R0

PUSH R1

LOAD_R1 R0



VM_CALL 4

POP R1

PUSH R0

PUSH R1

F_DIV


POP R5

PUSH MainClass.tan30
CALLF Console.WriteLine

LOAD_R1 R5



VM_CALL 4

LOAD_R0 10

VM_CALL 0

PUSH MainClass.PI
CALLF Console.WriteLine

PUSH 1.0

F_ATAN


PUSH 4.0

F_MUL


POP R1

VM_CALL 4

VM_EXIT


_end_start:
_data:

MainClass.sin30: db 'sin(30r): ', 0
MainClass.cos30: db '----cos(30r): ', 0
MainClass.tan30: db '-----tan(30r):*+/,./?';:"!@#$%^&*() ', 0
MainClass.PI: db '= ', 0
_end_data:
_bss:
_end_bss: