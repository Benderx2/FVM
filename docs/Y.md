<h1>The Y programming Language</h1>
The Y programming language is the only high-level (actually not) programming language available for FVM. <br>
It's an object-oriented form of assembly. <br>
The name 'Y' has no significance to FVM and the reason shall remain enclosed. <br>
<code>class</code> keyword.<br>
Declares a class. This class can contain various data types.<br>
<code>proc</coe> keyword.<br>
Declares a procedure, can only contain code.<br>
Example:
<code>
class MainClass { <br>
	int a = 0 <br>
	int b = 0
	string string1 = " Hello "
	proc Main {
		
	}
}
</code>
<h2>Data Types</h2>
Y has only 2 data types<br>
int - Integer.<br>
string - String (NULL terminated)<br>
<h2>Sample Code</h2>
Hello World in Y: <br>
<code>
class MainClass {
	string string1 = " Hello, World "
	proc Main {
		LOAD_R0 MainClass->string1
		CALLF Console->print
		VM_EXIT
	}
}
class Console {
	proc print {
		PUSH R0	
		PUSH R1
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
}
</code>
Compile with:
<code>
mono yc.exe hello.y hello.asm
fasm hello.asm (assuming you've got the a32.inc file under examples/ directory)
</code>
