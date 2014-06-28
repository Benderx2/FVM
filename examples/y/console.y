class MainClass {
	proc Main {
		LOAD_R0 Console->WriteLine
		LOAD_R0 Console->WriteInt
		LOAD_R0 Console->NewLine
	}
}
class Console {
	int newline = 10 /** newline = 0x0a or 10 **/
	proc WriteLine {
		/** Push registers to be used **/
		PUSH R1 
		PUSH R0	
		/** Load from Stack pointer **/
		LOAD_FROM_SP 4
		LOAD_R0 R1
		.loop:
		/** LODSB **/
		LOAD_BYTE
		/** Null char reached? **/
		CMPR R1, 0
		/** Done **/
		JMPF_E .done
		/** Else, print char **/
		VM_CALL 0	
		/** Loop again **/
		JMPF .loop
		.done:
		/** Pop and return **/
		POP R0
		POP R1
		RETF
	}
    proc WriteInt {
		LOAD_FROM_SP 4
		VM_CALL 3
		RETF
	}
    proc NewLine {
		LOAD_R0 Console->newline
		VM_CALL 0
		RETF
	}
}
