#!/bin/bash
# There shouldn't be any problems while using this, if there are well set this to 0
use_awesome_optimization=1
# Better change this to your fucking directory ok?
export FVM_INCLUDE=./include/ 
export SDL_INCLUDE=/usr/include/SDL
if [ $use_awesome_optimization=1 ]
then 
export CFLAGS='-O3'
else 
export CFLAGS='-O0'
fi
set -o verbose
echo 'CFLAGS: ' $CFLAGS
gcc $CFLAGS -c fvm.c -o fvm.o -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99 
gcc $CFLAGS -c fvm/error.c -o error.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc $CFLAGS -c fvm/cpu/mem/memory.c -o mem.o -I$FVM_INCLUDE -Wall -pedantic -std=gnu99
gcc $CFLAGS -c fvm/rom/rom.c -o rom.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc $CFLAGS -c fvm/fcall/fcall.c -o fcall.o -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc $CFLAGS -c fvm/sdl.c -o sdl.o -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc $CFLAGS -c fvm/bitutils.c -o bitutils.o -Wall -Wextra -pedantic -std=gnu99
gcc $CFLAGS -c fvm/cpu/cpu.c -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc $CFLAGS -c fvm/cpu/mem/vmm.c -o vmm.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc $CFLAGS -c fvm/rom/fv11.c -o fv11.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
fasm examples/mtask.asm 
mv examples/mtask.bin .
gcc -o fvm.out fvm.o error.o mem.o rom.o fcall.o sdl.o bitutils.o vmm.o fv11.o  cpu.o -lSDL -lSDL_ttf -pthread
# Remove all object files
rm *.o
echo 'FVM Compilation Complete.'
