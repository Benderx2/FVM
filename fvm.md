FVM Instruction Set
===
SLP - Processor Sleep<br>
LD0 - Load R0<br>
LD1 - Load R1<br>
LD2 - Load R2 <br>
LD3 - Load R3 <br>
LD4 - Load R4 <br>
LD5 - Load R5 <br>
LD12 - Load Stack Pointer <br>
JTX - Jump to address <br>
FCALL - Call Operating System specific function<br>
CALL - Call a procedure<br>
RET - Jump to return address on stack.<br>
PUSH - Push a 32-bit value on stack <br>
POPR - Pop off a 32-bit value from stack in a register<br>
LD1FA0 - Load a BYTE into R1 from address at R0 and increment R0<br>
ST1TA0 - Store a BYTE into addres R0 from the value of R1<br>
CMPV - Compare Register with "Value"<br>
JEX - Jump if Equal Flag is set<br>
JGX, JLX - Jump if Greater Than and Lesser than Flag are set<br>
DEBUG - Dump CPU Status <br>
LITH - Load Interrupt. (R0 - Interrupt number (max 255), R1 - Interrupt address (aligned))<br>
INT - Execute interrupt <br>
EXIT - Exit Program <br>
