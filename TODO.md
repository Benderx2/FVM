<h1>TODO List</h1>
Flouronix Virtual Machine - Version 0.2.0.0 <br>
Note: '/' stands for the FVM source directory.<br>
<h1>Code Rewrite/Modifications</h1>
/fvm/cpu/cpu.c:135:25 - Use switch instead of if(){}<br>
/fvm/cpu/cpu.c:174:25 - Clean up VM_CALL code<br>
/fvm/cpu/cpu.c:250:25 & /fvm/cpu/cpu.c:420:25 & /fvm/cpu/cpu.c:452:25 - Change if(){} to switch(){}<br>
/fvm/cpu/cpu.c:493:25 - Incorporate AND, XOR, OR in one switch(){} statement<br>
/fvm/devices/video.c:0:0 - Complete FGX video card emulation<br>
/fvm/initrd/initrd.c:13:9 - Add better error handling<br>
/fvm/rom/fv11.c:16:9 - Remove int32_t's a use direct references.<br>
/fvm/sdl.c:155:1 - Add checks for buffer overflows<br>
/fvm.c:86:9 - Use pthread to actually do something useful.<br>
/include/fvm/cpu/cpu.h:32:9 - Use arrays instead of registers <br>
/include/fvm/fv11/fv11.h - Replace int32_t's with uint32_t's <br>
/tools/compiler/yc/Main.cs:0:0 - Do full rewrite<br>
/tools/diskgen/diskgen.c:0:0 - Add support for naming disk image instead of just using "initrd.img"<br>
/tools/fdisasm/fdisasm.c:0:0 - Finish dissassembler<br>
/build.sh - Replace "build.sh" with Makefile<br>
<h1>Long-term Features</h1>
FPU - Add a (stack-based) floating point unit to the FVM instruction set. <br>
NATIVE BRIDGE - Implementation of the native bridge, programs will be able to<br>
call other procedures that are written in C/C++/Assembler.<br>
VIRTUAL ADDRESSING: Implement virtual addressing in the FVM architecture<br>
(/fvm/cpu/mem/vmm.c, /fvm/cpu/mem/vmm.h)<br>


