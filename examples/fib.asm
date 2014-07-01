include 'a32.inc'
_start:
LOAD_R0 string
CALLF print
LOAD_R1 5
XOR R1, R1
VM_DEBUG
LOAD_R0 15
LOAD_R1 25
ADDR R0, R1
VM_DEBUG
LOAD_R0 R1
CMPR R0, R1
JMPF_E .equal
;; this line wont be printed
LOAD_R0 not_equal_string
CALLF print
.equal:
LOAD_R0 fib_test
CALLF print
CALLF do_fib_test
VM_EXIT
print:
PUSH R0
PUSH R1
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
do_fib_test:
LOAD_R0 1	
LOAD_R2 0
LOAD_R3 1
.ploop:
; R3 = 1
; R0 = 1
; R0 + R3 = R0 = 2
; R3 = 1
; R0 = 2
; R3 = 1
; R0 + R3 = R0 = 3
; R3 = 2
; ???
LOAD_R3 R4
LOAD_R4 R0
ADDR R0, R3
LOAD_R1 R0
VM_CALL 3
LOAD_R1 ' '
VM_CALL 0
INCR R2
CMPR R2, 12
JMPF_E .done
JMPF .ploop
.done:
RETF
_end_start:
_data:
string: db 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 0
not_equal_string: db 'R0 and R1 aren"t equal FAIL', 0
fib_test: db 'Fibonacci Test....', 0x0A, 0
_end_data:
_bss:
_end_bss:
