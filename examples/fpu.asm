include 'a32.inc'
_start:
	LOAD_R0 1.0	
	LOAD_R1 1.0
	.iloop:
	; push r0
	PUSH R0
	; calculate factorial 
	F_FACT
	; pop factorial into r3
	POP R3
	; do a 1 / factorial
	PUSH 1.0
	PUSH R3
	F_DIV
	; pop result into r2
	POP R2
	; add it to r1
	PUSH R1
	PUSH R2
	F_ADD
	POP R1
	; increment r0
	PUSH 1.0
	PUSH R0
	F_ADD
	; store increment result
	POP R0
	VM_DEBUG
	; r0 = 8.0? 
	CMPR R0, 16.0
	JMPF_E .done
	JMPF .iloop
	.done:
	VM_CALL 4
	VM_EXIT
_end_start:
_data:
_end_data:
_bss:
_end_bss:
