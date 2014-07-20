;; Simple test. Compile with FASM.
;; macros for fasm
include 'a32.inc'
_start:
;; Register Interrupt Handler
LOAD_R0 0x01 ;; Register ISR 1
LOAD_R1 int1a ;; Load ISR Handler Address
LOAD_INTERRUPT ;; Load Interrupt!
;; Task 0 Infinite Loop!
SUBLEQ _data.d2, _data.d1, troll
VM_DEBUG
dead_end:
troll:
	JMPF dead_end
task1:
	LOAD_R1 'A'
	VM_CALL 0
	JMPF task1
task2:
	LOAD_R1 'B'
	VM_CALL 0
	JMPF task2
int1a:
	LOAD_SP 1000 ;; Load kernel stack
	;; Push R0 and R1
	PUSH R0
	PUSH R1
	;; Load the variable which_task
	LOAD_R0 which_task
	;; Grab the byte
	LOAD_BYTE
	;; Is R0 = 0 (Switch to task 1)
	CMPR R1, 0
	JMPF_E .task_1
	;; Or 1 (switch to task 1)
	CMPR R1, 1
	JMPF_E .task_2
.task_1:
	;; Set the which_task to 1 (will make the routine switch to the next task)
	LOAD_R0 which_task
	;; Load 1
	LOAD_R1 1
	;; Copy it
	STORE_BYTE
	;; Pop off CPU Registers
	POP R1
	POP R0
	;; Push the address / 4 (since it needs to be aligned)
	PUSH task1 / 4
	;; Return from interrupt
	IRETF
.task_2:
	LOAD_R0 which_task 
	LOAD_R1 0
	STORE_BYTE
	POP R1
	POP R0
	PUSH task2 / 4
	IRETF
_end_start:
_data:
.d1:
db 0
.d2:
db 1
which_task: db 0
_end_data:
_bss:
_end_bss:
