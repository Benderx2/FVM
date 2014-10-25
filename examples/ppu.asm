include 'a32.inc'
_start:
	PUSH _alien
	PUSH _end_data - _alien
	PUSH 56
	PPU_WRITE	
	PPU_UPDATE
	VM_EXIT
_end_start:
_data:
_alien:	
	file 't.rgba'
_end_data:
_bss:
_end_bss:
