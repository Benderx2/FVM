org 0
align 4
include 'a32.inc'
LOAD_R0 hello_string
CALLF print
read_key:
	VM_CALL 1
	CMPV R1, 0
	JMPF_E read_key
	VM_CALL 0
	CMPV R1, 13
	JMPF_E .done
	CMPV R1, 10
	JMPF_E .done
	JMPF read_key
.done:
	VM_EXIT
print:
	PUSH R0
	PUSH R1
.p1:
	;; Push (Save Register States)
	;; Load BYTE from R0 into R1 (LODSB)
	LOAD_BYTE
	;; Call VM Specific Function
	VM_CALL 0
	;; CMPV - Compare Value, Is R1 == NULL?
	CMPV R1, 0
	;; Yes. We're done
	JMPF_E .done	
	;; ...Or print again
	JMPF .p1
.done:
	POP R1
	POP R0
	RETF
hello_string: db 'Hello, Welcome to my Application', 0x0A, 'This is for testing keyboard input', 0
