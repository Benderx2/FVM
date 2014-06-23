#!/bin/bash
# Better change this to your fucking directory ok?
export FVM_INCLUDE=./include/ 
#!/bin/bash
export SDL_INCLUDE=/usr/include/SDL
set -o verbose
gcc -O2 -c fvm.c -o fvm.o -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99 
gcc -O2 -c fvm/error.c -o error.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -O2 -c fvm/cpu/mem/memory.c -o mem.o -I$FVM_INCLUDE -Wall -pedantic -std=gnu99
gcc -O2 -c fvm/rom/rom.c -o rom.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -O2 -c fvm/fcall/fcall.c -o fcall.o -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -O2 -c fvm/sdl.c -o sdl.o -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -O2 -c fvm/bitutils.c -o bitutils.o -Wall -Wextra -pedantic -std=gnu99
gcc -O2 -c fvm/cpu/cpu.c -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -O2 -c fvm/cpu/mem/vmm.c -o vmm.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -O2 -c fvm/rom/fv11.c -o fv11.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
fasm examples/mtask.asm 
mv examples/mtask.bin .
gcc -o fvm.out fvm.o error.o mem.o rom.o fcall.o sdl.o bitutils.o vmm.o fv11.o  cpu.o -lSDL -lSDL_ttf -pthread
# Remove all object files
rm *.o
echo 'FVM Compilation Complete.'
