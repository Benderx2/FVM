include 'a32.inc'
_start:
PUSH R0
JMPF MainClass.Main
MainClass.Main:


LOAD_R0 MainClass.string1


CALLF MainClass.print

VM_EXIT


MainClass.print:

PUSH R1


PUSH R0


.loop:


LOAD_BYTE


CMPR R1,0


JMPF_E .done


VMCALL
0


JMPF .loop


.done:


POP R0


POP R1


RETF


_end_start:
_data:

MainClass.string1: db 'Hello, World ', 0
_end_data:
_bss:
_end_bss: