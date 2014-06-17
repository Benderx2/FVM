FVM
===

Flouronix Virtual Machine. A 32-bit Machine written in C<br>
<h1>Compiling and Running</h1>
Please use the GNU C Compiler, (from gcc.gnu.org), and the GNU Binutils. You'll need a <br>
system linker which produces binaries for your system. Along with all this you'll also need <br>
a standard C library for your system. Mainly cstdio, cstdlib, cstdint, cstring, cstdbool.<br>
Then you must compile all the *.c files into object files, and link them to create an executable that<br>
runs on your system. Note that the sources use angle brackets, so you must tell the compiler the source directory through the<br>
-I flag<br>
It's recommended that you compile with these options '-Wall -Wextra -pedantic -std=gnu99 -I$FVM_INCLUDE (where FVM_INCLUDE is your directory where you downloaded the sources)'. <br>
There is a readymade build script for bash users. 
<h1>Using the emulator</h1>
The emulator isn't usbale for running at least "okayish" programs (YET.), but there is a hello world program that can be compiled using fasm.<br>
But anyways the syntax is: <br>
<pre>fvm [memory] [ROM Image Name]</pre>
<h1>Points of Interest</h1>
Well, I was always interested in computers, and my interest grew more as I approached<br>
the OSDev.org people. As I got closer and closer to bare metal, it made me think: "Why not write your own bare metal if you've come this far?" :D<br>
<h1>Contributing</h1>
Please DON'T! I will not accept any changes, because this project isn't something like "FVM FTW!", it's a personal learning project<br>
If you think this crap toy is good for you (the code isn't what I personally call "good", neither the emulator is close to "functional"), better fork() it. If you badly want to contribute something (until you burst out), better it be a bug or a suggesstion, no code. At least it runs a multitasker though :).
This readme and the emulator aren't complete btw.
<h1>TODO</h1>
Add new GPU Instructions <h1>
Add new CPU instructions (XOR, BTS, SHL, SHR, AND, NAND (:D))	
