include 'cpu.inc'
_start:
LOAD_R0 welcome_msg
CALLF vm_print_string
LOAD_R0 buffer
CALLF vm_read_string
LOAD_R1 hello_string
LOAD_R0 buffer
LOAD_R2 5
MEMCMP
JMPF_E .news
JMPF .exit
.news:
	LOAD_R0 string
	CALLF vm_print_string
.exit:
VM_EXIT
include 'vm_screen.asm'
welcome_msg: db 'Welcome to Flouronix OG Alpha 0.01',13, 0
hello_string: db 'HELLO', 0
string: db 'You guessed it!', 13, 0
buffer: times 256 db 0
_end_start:
_data:
_end_data:
_bss:
_end_bss:
