DEFINE F_CON_WRITE 0
DEFINE F_CON_READ 1
DEFINE R0 -257
DEFINE R1 -258
DEFINE R2 -259
DEFINE R3 -261
DEFINE R4 -262
DEFINE R5 -263
DEFINE R12 -260
macro slp 
{	
	dd 0x00
}
macro ld0 val
{
	dd 0x01
	dd val
}
macro ld1 val
{
	dd 0x03
	dd val
}
macro ld2 val
{
	dd 0x0d
	dd val
}
macro ld3 val
{
	dd 0x16
	dd val
}
macro ld4 val
{
	dd 0x17
	dd val
}
macro ld5 val
{
	dd 0x18
	dd val
}
macro fcall val
{
	dd 0x02
	dd val
}
macro jtx addr
{
	dd 0x04
	dd addr
}
macro push val
{
	dd 0x08
	dd val
}
macro popr reg
{
	dd 0x9
	dd reg
}
macro debug
{
	dd 0x0A
}
macro exit 
{
	dd 0xFF
}
macro ld1fa0
{
	dd 0xB
}
macro call addr
{
	dd 0xC	
	dd addr
}
macro ret
{
	dd 0x06
}
macro cmpv register, value
{
	dd 0x0E
	dd register
	dd value
}
macro jex address
{
	dd 0x0F
	dd address
}
macro st1ta0 
{
	dd 0x12
}
macro END
{
	dd 0xFFFFFFFF
}
macro ld12 val
{
	dd 0x07
	dd val
}
macro int number
{
	dd 0x13
	dd number
}
macro lith
{
	dd 0x14
}
macro iret
{
	dd 0x15
}
macro decr reg
{
	dd 0x19
	dd reg
}
macro incr reg
{
	dd 0x1A
	dd reg
}
macro in0 port
{
	dd 0x1D
	dd port
}
macro out0 port
{
	dd 0x1C
	dd port
}


