;; Simple test. Compile with FASM.
;; macros for fasm
include 'fvm.inc'
push 0x09
;; Pop 0x09 into R1
pop1
;; execute debug instruction 
debug
;; Load R1 into R0
ld0 R1
;; Load R0 with ASCII 'H'
ld0 'H'
;; Load R1 with R0
ld1 R0
;; Reload R0 with F_CON_WRITE (Means, write to stdout)
ld0 F_CON_WRITE
;; Call the Virtual Machine specific function
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
ld ' '
fcall
;; Exit
exit
