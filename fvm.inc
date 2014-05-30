DEFINE F_CON_WRITE 0
DEFINE R0 -257
DEFINE R1 -258

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
macro fcall val
{
	dd 0x02
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
macro pop1
{
	dd 0x9
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
macro ccall
{
	dd 0xC	
}
macro fret
{
	dd 0x06
}

