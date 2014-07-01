$include console.h
class MainClass {
	string sin30 = " sin(30r): "
	string cos30 = " ----cos(30r): "
	string tan30 = " -----tan(30r): "
	proc Main {	
		/** Invoke Console->WriteLine **/
		INVOKE Console->WriteLine MainClass->sin30
		PUSH 30.0
		F_SINX
		POP R1
		VM_CALL 4
		INVOKE Console->WriteLine MainClass->cos30
		PUSH 30.0 
		F_COSX
		POP R0
		PUSH R1
		LOAD_R1 R0	
		VM_CALL 4
		POP R1
		PUSH R0
		PUSH R1
		F_DIV
		POP R5
		INVOKE Console->WriteLine MainClass->tan30
		LOAD_R1 R5 
		VM_CALL 4
		VM_EXIT
	}
}
		
