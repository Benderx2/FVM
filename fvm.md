FVM Instruction Set
===
SLP - Processor Sleep<br>
LD0 - Load Register R0 with value (if value is -258 then it means that Load R0 with value of R1)<br>
LD1 - Load Register R1 with value (if value is -257 then it means that Load R0 with value of R0)<br>
LD2 - Load Register R2 (Call Address Register) (if address is -257 or -258 then it means R0 or R1 respectively) <br>
LD12 - Load Stack Pointer <br>
JTX - Jump to address <br>
FCALL - Call Operating System specific function (Arguments are R0 and R1)<br>
CCALL - Jump to Address of value of R2 and set R17 to current instruction pointer + 1<br>
FRET - Jump to R17 and set R17 to 0.<br>
PUSH - Push a 32-bit value on stack <br>
POP1 - Pop off a 32-bit value from stack in R1 <br>
LD1FA0 - Load a BYTE into R1 from address at R0 and increment R0<br>
CMPV - Compare Register with "Value"<br>
JEX - Jump if Equal Flag is 0<br>
DEBUG - Dump CPU Status <br>
EXIT - Exit Program <br>
