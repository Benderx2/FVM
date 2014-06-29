$include console.h
class MainClass {
	string string1 = " Hello, FVM and Y world! "
	/** Alright, this is a simple compiler i wrote in C# for my Virtual Machine called FVM **/
	proc Main { 
		/** Main Procedure **/
		CALLPROC Console->WriteLine MainClass->string1 /** Call the WriteLine procedure **/
		/** Exit the VM **/
		VM_EXIT
	}
}
