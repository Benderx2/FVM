include 'a32.inc'
_start:
PUSH R0
JMPF MainClass.Main
MainClass.Main:
JMPF @f
include "console.lib"
@@:




PUSH MainClass.string1
CALLF Console.WriteLine



VM_EXIT


_end_start:
_data:

MainClass.string1: db 'Hello, FVM and Y world! ', 0
_end_data:
_bss:
_end_bss: