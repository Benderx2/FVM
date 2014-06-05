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
ld1 'H'
st1ta0
debug
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
read_key:
	jtx read_key
task1:
	ld1 'A'
	fcall 0
	jtx task1
task2:
	ld1 'B'
	fcall 0
	jtx task2
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
	ld12 800 ;; Load kernel stack
	push R0
	push R1
	ld0 which_task
	ld1fa0
	cmpv R1, 0
	jex .task_1
	cmpv R1, 1
	jex .task_2
.task_1:
	ld0 which_task
	ld1 1
	st1ta0
	popr R1
	popr R0
	push task1 / 4
	iret
.task_2:
	ld0 which_task
	ld1 0
	st1ta0
	popr R1
	popr R0
	push task2 / 4
	iret

string: db 'Fello FVM World! 1234567890+-*=()', 0x0A, 'Please Type in something: ', 0x0A, 0
int_string: db 0x0A, 'This is called from INT 1!', 0
which_task: db 0
END
