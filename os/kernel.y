$include modules/terminal.h
class MainClass {
	string HelloKernel = " Hello, kernel world! "
	proc Main {
		INVOKE Console->WriteLine MainClass->HelloKernel
		VM_EXIT
	}
}
