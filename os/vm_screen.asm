; Screen calls for VM.
; Input - R0 : Location of string
vm_print_string:
	; Save regs
	PUSH R0
	PUSH R1
.print_loop:
	; Grab byte
	LOAD_BYTE
	; End of string?
	CMPR R1, 0
	JMPF_E .end_print
	; Print the character
	VM_CALL 0x0
	JMPF .print_loop
.end_print:
	; Restore and return 
	POP R1
	POP R0
	RETF
; Input - R1 : Integer
vm_print_int:
	VM_CALL 0x3
	RETF
; Input - R1 : Float
vm_print_float:
	VM_CALL 0x4
	RETF
; Input - Nothing
; Output - R1 : Read Character
vm_read_key:
.read_again:
	VM_CALL 0x1
	CMPR R1, 0
	JMPF_E .read_again
	RETF
; Input - R0 : Buffer (Max = 256bytes)
; Output - Nothing (Buffer filled)
vm_read_string:
	PUSH R0
	PUSH R1
	PUSH R2
	XOR R2, R2
.read_loop:
	CALLF vm_read_key
	; Enter?
	CMPR R1, 13
	JMPF_E .read_done
	; 256 bytes read?
	CMPR R2, 256
	JMPF_G .read_done
	; Else store it.
	STORE_BYTE
	; And print
	VM_CALL 0x0
	INCR R2
	JMPF .read_loop
.read_done:
	LOAD_R1 0
	STORE_BYTE
	POP R2
	POP R1
	POP R0
	RETF
; Input - R0 : String
; Output - R2 : Length
vm_get_string_length:
	PUSH R0
	PUSH R1
	XOR R2, R2
.get_len:
	LOAD_BYTE
	CMPR R1, 0
	JMPF_E .len_done	
	INCR R2
	JMPF .get_len
.len_done:
	POP R1
	POP R0
	RETF
; Input - R0 : First String
; Input - R1 : Second String
; Output - E set if equal, E unset if not.
vm_compare_string:
	MEMCMP
	RETF
