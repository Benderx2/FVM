class MainClass {
	int volume = 500
	int damage = 300
	string string1 = " Hello, World "
	proc Main {
		LOAD_R0 MainClass->string1
		.loop:
		LOAD_BYTE
		CMPR R1, 0
		JMPF_E .done
		VM_CALL 0
		JMPF .loop
		.done:
		VM_EXIT
	}
	
}
