include 'a32.inc'
dd 0xC001E5
dd _start
dd _start
dd _end_start - _start
db 'YCOMPILR'
_start:
PUSH R0
JMPF MainClass.Main
MainClass.Main:
LOAD_R0 MainClass.string1
JMPF $+MainClass.string1.strlen
MainClass.string1: db 'Hello, World '
.strlen: dd $-MainClass.string1
