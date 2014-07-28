include 'a32.inc'
_start:
PUSH R0
JMPF MainClass.Main
MainClass.Main:
; whoops :P
; This is a simple application written for the VM!
; As you can see we do a "NATIVE_CALL" instruction right here.

NATIVE_CALL lib_test,proc_test,0

VM_EXIT


_end_start:
_data:
lib_test: db "./test.so", 0 ; Is the name of the library.
proc_test: db "test_function", 0 ; Is the name of our function
_end_data:
_bss:
_end_bss:
