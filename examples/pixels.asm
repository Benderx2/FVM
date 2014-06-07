org 0
align 4
include 'fvm.inc'
main:
	ld0 0
	ld1 0
	ld2 0xFFFFFFFF
	fcall 2
	incr R1
	fcall 2
	exit
