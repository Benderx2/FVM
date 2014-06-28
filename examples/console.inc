Console.WriteLine:


PUSH R0

PUSH R1

LOAD_FROM_SP 4

LOAD_R0 R1



.loop:


LOAD_BYTE


CMPR R1,0

JMPF_E .done

VM_CALL 0

JMPF .loop

.done:


POP R1

POP R0

RETF


Console.WriteInt:



VM_CALL 3

RETF


Console.NewLine:


LOAD_R1 10

VM_CALL 0

RETF

