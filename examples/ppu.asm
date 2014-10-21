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
	db 37, 34, 32, 64, 255, 0, 23, 24, 56, 60, 20, 84, 72
_end_data:
_bss:
_end_bss:
