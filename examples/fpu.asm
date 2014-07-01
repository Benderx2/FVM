include 'a32.inc'
_start:
	; 30 radians
	PUSH 30.0
	F_SINX
	POP R0
	PUSH 30.0
	F_COSX
	POP R1
	VM_CALL 4
	PUSH R1
	PUSH R0
	F_DIV
	POP R1
	VM_CALL 4
	VM_EXIT
_end_start:
_data:
_end_data:
_bss:
_end_bss:
