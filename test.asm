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
;debug
;; Load R1 into R0
ld0 R1
;; Load R0 with ASCII 'H'
ld0 'H'
;; Load R1 with R0
ld1 R0
;; Reload R0 with F_CON_WRITE (Means, write to stdout)
ld0 F_CON_WRITE
;; Call the Virtual Machine specific function
;; Load R0 with F_CON_WRITE
ld0 F_CON_WRITE
ld1 'H'
;; fcall - function call, call the F_CON_WRITE, with R1 = 'H'
fcall 
ld1 'E'
fcall 
ld1 'L'
fcall 
ld1 'L'
fcall 
ld1 'O'
fcall 
ld1 ' '
fcall 
ld1 'W'
fcall 
ld1 'O'
fcall 
ld1 'R'
fcall 
ld1 'L'
fcall 
ld1 'D'
fcall
ld1 ' '
fcall
;; Jump to sample1
jtx sample1
sample1:
;; Call Sample2
ld2 sample2
;; Exit
ccall
exit
sample2:
;; Load String address in R0
ld0 string+1
;; Grab a byte from R0
ld1fa0
;; Print that byte
ld0 F_CON_WRITE
fcall
;; Sleep for a while
slp
;; return from procedure
fret
;; Some string
string: db 'AOLX'
