; FGX - Flouronix Graphics X. lol.
; Shows a demonstration of using FGX to switch to higher resolutions
include 'a32.inc'
_start:
	LOAD_R0 320
	OUT 0x3D
	LOAD_R0 200
	OUT 0x3E
	LOAD_R0 32
	OUT 0x3F	
	; Set resolution
	LOAD_R0 0x47E3
	OUT 0x3B
.ploop:
	LOAD_R1 'V'
	VM_CALL 0
	JMPF .ploop
_end_start:
_data:
_end_data:
_bss:
_end_bss:
