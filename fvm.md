FVM Instruction Set
===
SLP - Processor Sleep<br>
LD0 - Load Register R0 with value (if value is -258 then it means that Load R0 with value of R1)<br>
LD1 - Load Register R1 with value (if value is -257 then it means that Load R0 with value of R0)<br>
LD2 - Load Register R2 <br>
LD12 - Load Stack Pointer <br>
JTX - Jump to address <br>
FCALL - Call Operating System specific function<br>
CCALL - Call a procedure<br>
FRET - Jump to R17 and set R17 to 0.<br>
PUSH - Push a 32-bit value on stack <br>
POPR - Pop off a 32-bit value from stack in a register<br>
LD1FA0 - Load a BYTE into R1 from address at R0 and increment R0<br>
ST1TA0 - Store a BYTE into addres R0 from the value of R1<br>
CMPV - Compare Register with "Value"<br>
JEX - Jump if Equal Flag is set<br>
JGX, JLX - Jump if Greater Than and Lesser than Flag are set<br>
DEBUG - Dump CPU Status <br>
EXIT - Exit Program <br>
