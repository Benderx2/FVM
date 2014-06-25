; C Default Calling convention
include 'a32.inc'
_start:
	PUSH string_address
	CALLF print
	VM_EXIT
print:
	PUSH R0
	PUSH R1
	LOAD_FROM_SP 4
	LOAD_R0 R1
	; For debugging
	VM_DEBUG
.ploop:
	LOAD_BYTE
	CMPR R1, 0
	JMPF_E .done
	VM_CALL 0
	JMPF .ploop
.done:
	POP R1
	POP R0
	RETF
_end_start:
string_address:
_data:
	db 'Hello, World from cdecl', 0x0A, 0
_end_data:
_bss:
_end_bss:
