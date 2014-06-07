;; Simple test. Compile with FASM.
;; macros for fasm
include 'fvm.inc'
use32
org 0
;; Align addresses to 4-bytes please
align 4
;; Load Address of string into R1
ld0 string
ld1 'H'
;; Store 'H'
st1ta0
ld0 string
;; Call print
call print
;; Sample shit
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
;; Task 0 Infinite Loop!
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
	ld12 1000 ;; Load kernel stack
	;; Push R0 and R1
	push R0
	push R1
	;; Load the variable which_task
	ld0 which_task
	;; Grab the byte
	ld1fa0
	;; Is R0 = 0 (Switch to task 1)
	cmpv R1, 0
	jex .task_1
	;; Or 1 (switch to task 1)
	cmpv R1, 1
	jex .task_2
.task_1:
	;; Set the which_task to 1 (will make the routine switch to the next task)
	ld0 which_task
	;; Load 1
	ld1 1
	;; Copy it
	st1ta0
	;; Pop off CPU Registers
	popr R1
	popr R0
	;; Push the address / 4 (since it needs to be aligned)
	push task1 / 4
	;; Return from interrupt
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
