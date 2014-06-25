include 'a321.inc'
dd 0xC001E5
dd _start
dd _start
dd _end_start - _start
db 'YCOMPILR'
_start:
PUSH R0
JMPF MainClass.Main
MainClass.Main:
include 'a321.inc'
dd 0xC001E5
dd _start
dd _start
dd _end_start - _start
db 'YCOMPILR'
_start:
PUSH R0
JMPF MainClass.Main
MainClass.Main:


