include 'a32.inc'
_start:
PUSH R0
JMPF MainClass.Main
MainClass.Main:


NATIVE_CALL lib_test,proc_test,0

VM_EXIT


_end_start:
_data:
lib_test: db "test.so", 0
proc_test: db "test_function", 0
_end_data:
_bss:
_end_bss:
