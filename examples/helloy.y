require "console.inc"
externproc Console->WriteLine
externproc Console->WriteInt
externproc Console->NewLine
class MainClass {
	string string1 = " Hello, World "
	proc Main {
		CALLPROC Console->WriteLine MainClass->string1
		VM_EXIT
	}
	
}
