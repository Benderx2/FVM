FVM
===
![alt tag](http://i.imgur.com/cq0EQDP.png)<br>
<i>An FVM application calls a shared library which displays a bitmap.</i><br>
<h2>The Flouronix Virtual Machine Architecture (or FVM)</h2>
<h2>INTRODUCTION</h2>
The Flouronix Virtual Machine was written to provide a secure and architecture-independant userspace to the Flouronix operating system.<br>
The virtual machine features a 32-bit address space, a stack, 6 general purpose registers, <br>
various arithmetic instructions and <i>is</i> turing complete. For now the machine is incapable for doing most of the things <br>
today's virtual architectures (.NET, Java...) can achieve. <br>There are future plans to develop a programming language for FVM, but sthat is not the current focus. <br>
The architecure is a RISC-like architecture, and <i>most</i> of the operations are<br>only performed on CPU registers. There are a special
set of instructions that can modify or act on the memory. <br>
<h2>INSTRUCTION SET</h2>
Please see fvm.md.
<h2>COMPILATION AND TESTING</h2>
Please use the GNU C Compiler, the code has not been tested with any other  <br>compiler like clang, Visual C, ... So I don't
know if it's possible to use them. I'd be happy if anyone could do this for me. <br> 
Along with the GNU toolchain for your system, you'll also need the Simple-Direct-Media Layer (SDL for short), https://www.libsdl.org/.
The build has been tested with libSDL 1.2, It's recommended to compile it with<br> that version. It should work with the newer versions though
untested!<br>
For those who're using bash (or similar), there is a readymade "build.sh" script.<br> It does everything that's required and even builds a test multitasking
ROM! Non-bash users could modify the script given.<br>
There is a readymade binary called "fvm.out" for Linux, but please don't use it.<br> It is advisable to build the VM with toolchain that is configured 
for your system.<br>
Notes: The build system has not been tested with Windows or Mac, however it doesn't use anything<br> that's Linux specific so it should not
require much effort to get it up and running.
TESTING: <br>
To test FVM, first you must compile your ROM using FASM. <br>
<p>fasm romfile.asm</p><br>
Next, you should compile tools/diskgen/diskgen.c and use it to create a ROM Image like this <br>
<p>./diskgen rom1.bin rom1toinitrd.bin rom2.bin rom2toinitrd.bin .......</p><br>
After this you must specifiy the inital ROM when you're about to run the VM.<br>
./fvm.out memory romdisk.img initrom.bin
<h2>LICENSE</h2>
Please see LICENSE.
<h2>TODO</h2>
....


