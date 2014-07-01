$include console.h
class MainClass {
	string sin30 = " sin(30r) =  "
	string cos30 = "  cos(30r) =  "
	proc Main {	
		CALLPROC Console->WriteLine MainClass->sin30
		PUSH 30.0
		F_SINX
		POP R1
		VM_CALL 4
		CALLPROC Console->WriteLine MainClass->cos30
		PUSH 30.0 
		F_COSX
		POP R1
		VM_CALL 4
		VM_EXIT
	}
}
		
