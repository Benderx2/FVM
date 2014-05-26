;; Simple test. Compile with FASM.
;; macros for fasm
include 'fvm.inc'
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
;; Jump to address 0, loop
jtx 0
exit
;; Infinite Loop
;jtx 36
