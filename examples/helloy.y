require "console.inc"
externproc Console->WriteLine
externproc Console->WriteInt
externproc Console->NewLine
class MainClass {
	int volume = 500
	int damage = 300
	string string1 = " Hello, World "
	proc Main {
		LOAD_R0 MainClass->string1
		CALLF Console->WriteLine
		CALLF Console->NewLine
		LOAD_R1 MainClass->damage
		CALLF Console->WriteInt
		VM_EXIT
	}
	
}
