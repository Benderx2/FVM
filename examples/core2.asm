; Example of a FVM program using 2 FVM cores.
include 'a32.inc'
_start:
	; Intialize Core 2 with IP as "task2"
	INIT_MP task2
task1:
	LOAD_R1 '1'
	VM_CALL 0
	JMPF task1
task2:
	LOAD_R1 '2'
	VM_CALL 0
	JMPF task2
_end_start:
_data:
_end_data:
_bss:
_end_bss:
