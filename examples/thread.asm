include 'a32.inc'
_start:
	VM_CREATE_THREAD thread2, t_stack
	VM_CREATE_THREAD thread3, t_stack
	VM_CREATE_THREAD thread4, t_stack
thread1:
	LOAD_R1 'A'
	VM_CALL 0
	JMPF thread1
thread2:
	LOAD_R1 'B'
	VM_CALL 0
	JMPF thread2
thread3:
	LOAD_R1 'C'
	VM_CALL 0
	JMPF thread3
thread4:
	LOAD_R1 'D'
	VM_CALL 0
	JMPF thread4
t_stack:
	DECLARE_STACK_SPACE 50 ; 50 bytes of cool stack
_end_start:
_data:
_end_data:
_bss:
_end_bss:
