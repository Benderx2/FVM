$include console.h /** Include Header **/
class MainClass {	
	string string1 = " Hello, World "
	proc Main {
		/** Call procedure Console->WriteLine with MainClass->string1 as arguments **/
		CALLPROC Console->WriteLine MainClass->string1
		VM_EXIT
	}
	
}
