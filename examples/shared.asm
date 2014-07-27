include 'a32.inc'
; Yes we need an .so file
REQUIRE_SO = 1
so_init:
_start:
	NATIVE_CALL hello_lib, hello_proc, 0
	VM_EXIT  
_end_start:
_data:
hello_lib: DECLARE_NATIVE_LIB "./hello.so"
hello_proc: DECLARE_NATIVE_PROC "hello"
_end_data:
_bss:
_end_bss:
