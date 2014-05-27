;; Simple test. Compile with FASM.
;; macros for fasm
include 'fvm.inc'
<<<<<<< HEAD
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
=======
;; Load R0 with F_CON_WRITE
ld0 F_CON_WRITE
ld1 'H'
;; fcall - function call, call the F_CON_WRITE, with R1 = 'H'
>>>>>>> 11dbf7f8467eabb68c688bcbecaa6c518c6afa85
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
<<<<<<< HEAD
ld ' '
fcall
;; Exit
=======
;; Jump to address 0, loop
jtx 0
>>>>>>> 11dbf7f8467eabb68c688bcbecaa6c518c6afa85
exit
