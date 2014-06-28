include 'a32.inc'
_start:
PUSH R0
JMPF MainClass.Main
MainClass.Main:
JMPF @f
include "console.inc"
@@:

PUSH MainClass.string1
PUSH 300
CALLF Console.WriteLine

LOAD_R1 300

CALLF Console.WriteInt

VM_EXIT


_end_start:
_data:

MainClass.string1: db 'Hello, World ', 0
_end_data:
_bss:
_end_bss: