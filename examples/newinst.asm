include 'a32.inc'
_start:
	LOAD_R0 0
	PUSH R0
	POPF
	VM_DEBUG
	VM_EXIT
_end_start:
_data:
_end_data:
_bss:
_end_bss:
