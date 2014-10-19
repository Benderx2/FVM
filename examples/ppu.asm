include 'a32.inc'
_start:
	PUSH _alien
	PUSH _end_data - _alien
	PUSH 0
	PPU_WRITE	
	PPU_UPDATE
	VM_EXIT
_end_start:
_data:
_alien:	
	db 00011000b
	db 01100100b
	db 11000011b
	db 00001111b
	db 00011001b
	db 00110000b
	db 00110110b
	db 01111111b
	db 01111111b
	db 01111111b
	db 01110000b
	db 00110000b
	db 00111000b
	db 00011110b
	db 00001111b
	db 00000011b

	db 00001100b
	db 00010010b
	db 11100011b
	db 11111001b
	db 11001100b
	db 10000110b
	db 10110110b
	db 11111111b
	db 11111111b
	db 11111111b
	db 00000111b
	db 00000110b
	db 00001110b
	db 00111100b
	db 11111000b
	db 11100000b
_end_data:
_bss:
_end_bss:
