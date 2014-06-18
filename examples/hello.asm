org 0
align 4
include 'a32.inc'
LOAD_R0 string
CALLF print
LOAD_R1 5
XOR r1, r1
VM_DEBUG
LOAD_R0 r1
CMPR r0, r1
JMPF_E .equal
;; this line wont be printed
LOAD_R0 not_equal_string
CALLF print
.equal:
VM_EXIT
print:
	PUSH r0
	PUSH r1
.ploop:
	LOAD_BYTE
	CMPR r1, 0
	JMPF_E .done
	VM_CALL 0
	JMPF .ploop
.done:
	POP r1
	POP r0
	RETF
string: db 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 0
not_equal_string: db 'R0 and R1 aren"t equal FAIL', 0
