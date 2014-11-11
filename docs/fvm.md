FVM Instruction Set
(refer to a32.inc for the actual mnemonics)
===
<h1>CPU Instructions</h1>
V_SLEEP - Processor Sleep<br>
LOAD_R0 - Load R0<br>
LOAD_R1 - Load R1<br>
LOAD_R2 - Load R2 <br>
LOAD_R3 - Load R3 <br>
LOAD_R4 - Load R4 <br>
LOAD_R5 - Load R5 <br>
LOAD_SP - Load Stack Pointer <br>
OPERATE - Do a operation on two operands and store result in the first. (MUL_XY - multiply, SUB_XY - Subtract, DIV_XY - Divide, ADD_XY - Add, 
LOAD_R - Load register 1 with value of register 2 (replacement for the above) <br> 
LOAD_M - Load Memory from Register to Register. Loads value at operand 1 (4 bytes) to operand 2.<br>
JMPF - Jump to address (registers can be used ONLY for this jump as of yet) <br>
VM_CALL - Call Operating System specific function<br>
CALLF - Call a procedure<br>
RETF - Jump to return address on stack.<br>
PUSH - Push a 32-bit value on stack <br>
POP - Pop off a 32-bit value from stack in a register<br>
LOAD_BYTE - Load a BYTE into R1 from address at R0 and increment R0<br>
STORE_BYTE - Store a BYTE into addres R0 from the value of R1<br>
CMPR - Compare Register with "Value"<br>
JMPF_E - Jump if Equal Flag is set<br>
JMPF_G, JMPF_L - Jump if Greater Than and Lesser than Flag are set<br>
VM_DEBUG - Dump CPU Status <br>
LOAD_INTERRUPT - Load Interrupt. (R0 - Interrupt number (max 255), R1 - Interrupt address (aligned))<br>
INT - Execute interrupt <br>
IN - Take input from port into R0<br>
OUT - Output to port R0<br>
XOR - Do a bitwise eXclusive OR <br>
AND - Bitwise AND <br>
INCR - Add 1 to register <br>
DECR - Subtract 1 from register <br>
ADDR - Add register to register or operand <br>
SUBR - Subtract Register from register or operand <br>
MUL - Multiply Register with R0<br>
DIV - Divide Register with R0<br>
LOAD_REGISTER_DWORD - Load Register (DWORD) from address at R0 (can be UA)<br>
STORE_REGISTER_DWORD - Store Register (DWORD) to address at R0 (can be UA).<br>
LOAD_FROM_SP - Load Value into R1 from offset in stack. (Each offset is 4 bytes) <br>
SUBLEQ - SUBtract and brance if Less than or EQual to zero. <br>
EXIT - Exit Program <br>
VM_CREATE_THREAD - Create new thread with stack and IP (4-byte aligned) <br>
THREAD_EXIT - Exit current thread <br>
NATIVE_CALL - Call native procedure stored in library <br>
INIT_MP - Initialise Core II with IP <br>
GETMEM - Get System Memory (R1 - Memory)<br>
MEMCMP - Compare Memory Blocks (R1, R0 - Blocks, R2 - Size)<br>
MEMCPY - Copy Memory Bloacks (R0 - Dest, R1 - Src, R2 - Size)<br>
LSHIFT - Do Lshift <br>
RSHIFT - Do Rshift <br>
OR - Do bitwise OR <br>
PUSHF - Push Flags (first 8-bit = E, second 8-bit = G, third 8-bit = L; fourth 8-bit = Z)<br>
POPF - Pop flags (format same as PUSHF)<br>
DUP - Duplicate top value of stack and push.<br>
<h1>FPU Instructions </h1>
F_SINX - Load sine of number pushed to stack, and push the result. (rad) <br>
F_COSX - Load cosine of number pushed to stack, and push the result. (rad) <br>
F_ABS - Load absolute value of number pushed to stack, and push the result. (rad) <br>
F_POW - 1st operand on stack = base, second or last op on stack = power, push result on stack<br>
F_FACT - Take factorial and push to stack <br>
F_MUL - Multiply operands on stack <br>
F_DIV - Divide 1st op by second op and push result to stack <br>
F_ADD - Add operands on stack and and push result <br>
F_SUB - Subtract 1st op from second and push result <br>
F_ATAN - Calculate arctan of op on stack and push. <br>
F_ACOS - Calculate acos of op on stack and push <br>
F_ASIN - Calculate asin of op on stack and push <br>
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
PPU_UPDATE - Upadate screen 
