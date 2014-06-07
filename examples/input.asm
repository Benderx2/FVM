org 0
align 4
include 'fvm.inc'
ld0 hello_string
call print
read_key:
	fcall 1
	cmpv R1, 0
	jex read_key
	fcall 0
	cmpv R1, 13
	jex .done
	cmpv R1, 10
	jex .done
	jtx read_key
.done:
	exit
print:
	push R0
	push R1
.p1:
	;; Push (Save Register States)
	;; Load BYTE from R0 into R1 (LODSB)
	ld1fa0
	;; Call VM Specific Function
	fcall 0
	;; CMPV - Compare Value, Is R1 == NULL?
	cmpv R1, 0
	;; Yes. We're done
	jex .done	
	;; ...Or print again
	jtx .p1
.done:
	popr R1
	popr R0
	ret
hello_string: db 'Hello, Welcome to my Application', 0x0A, 'This is for testing keyboard input', 0
