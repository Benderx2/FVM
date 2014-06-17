use32
include 'fvm.inc'
org 0
align 4
ld0 integer
ld2 0
ldd R2
debug
exit
integer:
	dd 0xFFF300
