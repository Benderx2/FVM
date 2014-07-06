/** Terminal Module for Fluoronix **/
class Console {
	proc WriteLine {
		/** Load first argument into R1 **/
		LOAD_ARG $1
		LOAD_R0 R1
		.loop:
		LOAD_BYTE
		CMPR R1, 0
		JMPF_E .done
		/** print character **/
		VM_CALL 0
		JMPF .loop
		.done:
		RETF
	}
	proc WriteFloat {
		LOAD_ARG $0
		VM_CALL 4
		RETF
	}
	proc WriteInt {	
		VM_CALL 3
		RETF
	}
		
}
