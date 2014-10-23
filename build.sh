#!/bin/bash
# Better change this to your fucking directory ok?
export FVM_INCLUDE=./include/ 
export SDL_INCLUDE=/usr/include/SDL
DFLAGS='' # Set this to 'g' if you want debugging info.
CFLAGS='-O3 -Werror -Wstrict-prototypes -Wmissing-prototypes -fstack-protector-all -Wall -Wextra -pedantic -Wno-strict-aliasing -std=gnu99' # Werror - Because I want to.
echo 'CFLAGS: ' $CFLAGS
echo 'Compilation Starting.....'
echo 'Compiling FVM tools []'
# Build the disk generator
gcc ./tools/diskgen/diskgen.c -o diskgen.out
# Build the romdump tool
gcc ./tools/romdump/romdump.c -o romdump.out
set -o verbose
# Build the VM now.
gcc $CFLAGS $DFLAGS -c fvm.c -o fvm.o -I$FVM_INCLUDE -I$SDL_INCLUDE  
gcc $CFLAGS $DFLAGS -c fvm/error.c -o error.o -I$FVM_INCLUDE 
gcc $CFLAGS $DFLAGS -c fvm/cpu/mem/memory.c -o mem.o -I$FVM_INCLUDE
gcc $CFLAGS $DFLAGS -c fvm/rom/rom.c -o rom.o -I$FVM_INCLUDE
gcc $CFLAGS $DFLAGS -c fvm/fcall/fcall.c -o fcall.o -I$FVM_INCLUDE -I$SDL_INCLUDE 
gcc $CFLAGS $DFLAGS -c fvm/sdl.c -o sdl.o -I$FVM_INCLUDE -I$SDL_INCLUDE 
gcc $CFLAGS $DFLAGS -c fvm/bitutils.c -o bitutils.o -I$FVM_INCLUDE
gcc $CFLAGS $DFLAGS -c fvm/cpu/cpu.c -I$FVM_INCLUDE -I$SDL_INCLUDE 
gcc $CFLAGS $DFLAGS -c fvm/cpu/mem/vmm.c -o vmm.o -I$FVM_INCLUDE 
gcc $CFLAGS $DFLAGS -c fvm/rom/fv11.c -o fv11.o -I$FVM_INCLUDE 
gcc $CFLAGS $DFLAGS -c fvm/initrd/initrd.c -o initrd.o -I$FVM_INCLUDE
gcc $CFLAGS $DFLAGS -c fvm/sighandle.c -o sighandle.o -I$FVM_INCLUDE
gcc $CFLAGS $DFLAGS -c fvm/fpu/fpu.c -o fpu.o -I$FVM_INCLUDE
gcc $CFLAGS $DFLAGS -c fvm/gc/objects.c -o objects.o -I$FVM_INCLUDE
gcc -std=gnu99 $DFLAGS -c fvm/devices/video.c -o video.o -I$FVM_INCLUDE -I$SDL_INCLUDE 
gcc $DFLAGS -c fvm/native/native.c -o native.o -std=gnu99  -I$FVM_INCLUDE -I$SDL_INCLUDE
gcc $DFLAGS -c fvm/thread/thread.c -o thread.o -std=gnu99 -I$FVM_INCLUDE
gcc $CFLAGS $DFLAGS -c fvm/mm/mm.c -o mm.o -std=gnu99 -I$FVM_INCLUDE
gcc $CFLAGS $DFLAGS -c fvm/cpu/m_cpu.c -o m_cpu.o -std=gnu99 -I$FVM_INCLUDE
gcc -o fvm.out fvm.o error.o mem.o rom.o fcall.o sdl.o bitutils.o vmm.o fv11.o native.o  cpu.o initrd.o thread.o sighandle.o fpu.o objects.o video.o mm.o m_cpu.o -lm -lSDL -lSDL_ttf -lSDL_image -ldl -pthread
# Remove all object files
rm *.o
echo 'FVM Compilation Complete.'
