FVM
===

Flouronix Virtual Machine. A 16-bit Machine written in C<br>
<h1>Compiling and Running</h1>
Please use the GNU C Compiler, (from gcc.gnu.org), and the GNU Binutils. You'll need a <br>
system linker which produces binaries for your system. Along with all this you'll also need <br>
a standard C library for your system. Mainly cstdio, cstdlib, cstdint, cstring, cstdbool.<br>
Then you must compile all the *.c files into object files, and link them to create an executable that<br>
runs on your system.<br>
It's recommended that you compile with '-Wall -Wextra -pedantic -std=gnu99'. <br>
There is a readymade build script for bash users. 
<h1>Using the emulator</h1>
The emulator isn't usbale (YET.), but there is a hello world program that can be compiled using fasm.<br>
But anyways the syntax is: <br>
<pre>fvm [memory] [ROM Image Name]</pre>
This readme isn't complete btw.
