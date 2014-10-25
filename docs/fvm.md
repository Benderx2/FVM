FVM Instruction Set
(refer to a32.inc for the actual mnemonics)
===
<h1>Implemented</h1>
SLP - Processor Sleep<br>
LD0 - Load R0<br>
LD1 - Load R1<br>
LD2 - Load R2 <br>
LD3 - Load R3 <br>
LD4 - Load R4 <br>
LD5 - Load R5 <br>
LD12 - Load Stack Pointer <br>
LOAD_R - Load register 1 with value of register 2 (replacement for the above) <br> 
LOAD_M - Load Memory from Register to Register. Loads value at operand 1 (4 bytes) to operand 2.
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
IN0 - Take input from port into R0<br>
OUT0 - Output to port R0<br>
XOR - Do a bitwise eXclusive OR <br>
AND - Bitwise AND <br>
INCR - Add 1 to register <br>
DECR - Subtract 1 from register <br>
ADDR - Add register to register or operand <br>
SUBR - Subtract Register from register or operand <br>
MUL - Multiply Register with R0<br>
DIV - Divide Register with R0<br>
LDD - Load Register (DWORD) from address at R0 (can be UA)<br>
STD - Store Register (DWORD) to address at R0 (can be UA).<br>
LOAD_FROM_SP - Load Value into R1 from offset in stack. (Each offset is 4 bytes) <br>
SUBLEQ - SUBtract and brance if Less than or EQual to zero. <br>
EXIT - Exit Program <br>
VM_CREATE_THREAD - Create new thread with stack and IP (4-byte aligned) <br>
THREAD_EXIT - Exit current thread <br>
NATIVE_CALL - Call native procedure stored in library <br>
INIT_MP - Initialise Core II with IP <br>
MEMCMP - Compare Memory Blocks (R1, R0 - Blocks, R2 - Size)<br>
GETMEM - Get System Memory (R1 - Memory)<br>
<h1>Instructions for PIC (Position Independent Code)</h1>
RELOC_JE - Jump if equal (relative to TLS->load_addr) <br>
RELOC_JL - Jump if lesser (relative to TLS->load_addr)<br>
RELOC_JG - Jump if greater (relative to TLS->load_addr) <br>
RELOC_JMP - Jump to address (relative to TLS->load_addr) <br>
RELOC_STD - Store to address or register, value of address is in R1 (relative to TLS->load_addr) <br>
RELOC_LDD - Load from address or a register pointing to an address into R1 (relative to TLS_load->addr) <br>
<h1>PPU Instructions</h1>
PPU_READ - Read from PPU 
PPU_WRITE - Write to PPU 
PPU_UPDATE - Upadte screen 
<h1>Not implemented instructions (Planned)</h1>
OR - Bitwise OR <br>
BTS - Bit set <br>
BTU - Bit Unset <br>
BTL - Bit Toggle <br>
BTC - Check for Bit <br>
LD1FA0W - Same as LD1FA0 but gives two bytes. <br>
ST1TA0W - Same as ST1TA0 but stores two bytes. <br>
