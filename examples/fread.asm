include 'a32.inc'
_start:
	LOAD_R0 file_name ; file name
	VM_CALL 0x5 ; fopen
	LOAD_R1 3 ; Length 
	LOAD_R2 file_string ; the file name 
	VM_CALL 0x7 ; Call the fread()
	LOAD_R0 file_string
.loopy:
	LOAD_BYTE
	CMPR R1, 0
	JMPF_E .endp
	VM_CALL 0x0
	JMPF .loopy
.endp:
	VM_EXIT
_end_start:
_data:
	file_name: db './FILE.TXT', 0
	file_string: times 10 db 0
	db 0
_end_data:
_bss:
_end_bss:
