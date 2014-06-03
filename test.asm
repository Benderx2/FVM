;; Simple test. Compile with FASM.
;; macros for fasm
include 'fvm.inc'
use32
org 0
;; Align addresses to 4-bytes please
align 4
ld2 490
ld12 R2
;; Load Stack Pointer
ld2 490
ld12 R2
push 0x09
;; Pop 0x09 into R1
popr R1
;; Load Address of string into R1
ld1 string
;; Load R1 into R0
ld0 R1
;; Call print
ccall print
read_key:
	fcall 1
	cmpv R1, 0
	jex read_key
	fcall 0
	jtx read_key
exit
print:
	;; Push (Save Register States)
	push R0
	push R1
	;; Load BYTE from R0 into R1 (LODSB)
	ld1fa0
	;; Call VM Specific Function
	fcall 0
	;; CMPV - Compare Value, Is R1 == NULL?
	cmpv R1, 0
	;; Yes. We're done
	jex .done	
	;; ...Or print again
	jtx print
.done:
	popr R1
	popr R0
	fret
string: db 'Hello FVM World! 1234567890+-*=()', 0x0A, 'Please Type in something: ', 0x0A, 0
END
