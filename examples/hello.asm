org 0
align 4
include 'fvm.inc'
ld0 string
call print
ld0 R1
cmpv R0, R1
jex .equal
;; this line wont be printed
ld0 not_equal_string
call print
.equal:
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
not_equal_string: db 'R0 and R1 aren"t equal FAIL', 0
