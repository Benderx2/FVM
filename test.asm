;; Simple test. Compile with FASM.
;; macros for fasm
include 'fvm.inc'
use32
org 0
;; Align addresses to 4-bytes please
align 4
push 0x09
;; Pop 0x09 into R1
popr R1
;; Load Address of string into R1
ld0 string
;; Call print
call print
ld0 25
ld1 30
ld2 0xF
fcall 2
incr R1
decr R5
;; Register Interrupt Handler
ld0 0x01 ;; Register ISR 1
ld1 int1a ;; Load ISR Handler Address
lith ;; Load Interrupt!
int 0x01 ;; Call Handler!
read_key:
	fcall 1
	cmpv R1, 0
	jex read_key
	cmpv R1, 0x0A
	jex .quit
	fcall 0
	jtx read_key
.quit:
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
int1a:
	push R0
	push R1
	ld0 int_string
	call print
	popr R1
	popr R0
	iret
string: db 'Hello FVM World! 1234567890+-*=()', 0x0A, 'Please Type in something: ', 0x0A, 0
int_string: db 0x0A, 'This is called from INT 1!', 0
END
