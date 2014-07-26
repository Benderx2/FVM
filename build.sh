#!/bin/bash
# There shouldn't be any problems while using this, if there are well set this to 0
use_awesome_optimization=1
# Better change this to your fucking directory ok?
export FVM_INCLUDE=./include/ 
export SDL_INCLUDE=/usr/include/SDL
if [ $use_awesome_optimization=1 ]
then 
export CFLAGS='-O3 -Werror -Wstrict-prototypes -Wmissing-prototypes -fstack-protector-all -Wall -Wextra -pedantic -Wno-strict-aliasing -std=gnu99' # Werror - Because I want to.
else 
export CFLAGS='-O0 -Werror -Wstrict-prototypes -Wmissing-prototypes -fstack-protector-all -Wall -Wextra -pedantic -std=gnu99'
fi
set -o verbose
echo 'CFLAGS: ' $CFLAGS
# Build the disk generator
gcc ./tools/diskgen/diskgen.c -o diskgen.out
# Build the romdump tool
gcc ./tools/romdump/romdump.c -o romdump.out
# Build the VM now.
gcc $CFLAGS -c fvm.c -o fvm.o -I$FVM_INCLUDE -I$SDL_INCLUDE  
gcc $CFLAGS -c fvm/error.c -o error.o -I$FVM_INCLUDE 
gcc $CFLAGS -c fvm/cpu/mem/memory.c -o mem.o -I$FVM_INCLUDE
gcc $CFLAGS -c fvm/rom/rom.c -o rom.o -I$FVM_INCLUDE
gcc $CFLAGS -c fvm/fcall/fcall.c -o fcall.o -I$FVM_INCLUDE -I$SDL_INCLUDE 
gcc $CFLAGS -c fvm/sdl.c -o sdl.o -I$FVM_INCLUDE -I$SDL_INCLUDE 
gcc $CFLAGS -c fvm/bitutils.c -o bitutils.o -I$FVM_INCLUDE
gcc $CFLAGS -c fvm/cpu/cpu.c -I$FVM_INCLUDE -I$SDL_INCLUDE 
gcc $CFLAGS -c fvm/cpu/mem/vmm.c -o vmm.o -I$FVM_INCLUDE 
gcc $CFLAGS -c fvm/rom/fv11.c -o fv11.o -I$FVM_INCLUDE 
gcc $CFLAGS -c fvm/initrd/initrd.c -o initrd.o -I$FVM_INCLUDE
gcc $CFLAGS -c fvm/sighandle.c -o sighandle.o -I$FVM_INCLUDE
gcc $CFLAGS -c fvm/fpu/fpu.c -o fpu.o -I$FVM_INCLUDE
gcc $CFLAGS -c fvm/gc/objects.c -o objects.o -I$FVM_INCLUDE
gcc $CFLAGS -c fvm/devices/video.c -o video.o -I$FVM_INCLUDE -I$SDL_INCLUDE
gcc $CFLAGS -c fvm/native/native.c -o native.o -I$FVM_INCLUDE
fasm examples/mtask.asm 
mv examples/mtask.bin .
./diskgen.out mtask.bin mtask.bin
gcc -o fvm.out fvm.o error.o mem.o rom.o fcall.o sdl.o bitutils.o vmm.o fv11.o native.o  cpu.o initrd.o sighandle.o fpu.o objects.o video.o -lm -lSDL -lSDL_ttf -pthread
# Remove all object files
rm *.o
echo 'FVM Compilation Complete.'
