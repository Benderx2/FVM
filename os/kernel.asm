include 'a32.inc'
_start:
PUSH R0
JMPF MainClass.Main
JMPF @f
include "terminal.lib"
@@:
MainClass.Main:


PUSH MainClass.HelloKernel
CALLF Console.WriteLine

VM_EXIT


_end_start:
_data:

MainClass.HelloKernel: db 'Hello, kernel world! ', 0
_end_data:
_bss:
_end_bss: