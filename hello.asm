org 0
align 4
include 'fvm.inc'
ld0 string
call print
exit
print:
	push R0
	push R1
.ploop:
	ld1fa0
	cmpv R1, 0
	jex .done
	fcall 0
	jtx .ploop
.done:
	popr R0
	popr R1
	ret
string: db 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 0
