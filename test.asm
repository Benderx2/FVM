;; Simple test. Compile with FASM.
;; macros for fasm
include 'fvm.inc'
use32
org 0
;; Align addresses to 4-bytes please
align 4
push 0x09
;; Pop 0x09 into R1
pop1
;; execute debug instruction 
ld1 string
;; Load R1 into R0
ld0 R1
ccall print
exit
;; Some string
print:
	ld1fa0
	fcall 0
	cmpv R1, 0
	jex .done
	jtx print
.done:
	fret
string: db 'Hi Guys, I made an OS :)', 0
