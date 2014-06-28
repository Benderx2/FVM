class MainClass {
	proc Main {
		LOAD_R0 Console->WriteLine
		LOAD_R0 Console->WriteInt
		LOAD_R0 Console->NewLine
	}
}
class Console {	
	int newline = 10
	proc WriteLine {
		PUSH R0
		PUSH R1
		LOAD_FROM_SP 4
		LOAD_R0 R1	
		.loop:
		LOAD_BYTE
		CMPR R1, 0
		JMPF_E .done
		VM_CALL 0
		JMPF .loop
		.done:
		POP R1
		POP R0
		RETF
	}
	proc WriteInt {	
		VM_CALL 3
		RETF
	}
	proc NewLine {
		LOAD_R1 Console->newline
		VM_CALL 0
		RETF
}
