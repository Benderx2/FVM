#!/bin/bash
# Better change this to your fucking directory ok?
export FVM_INCLUDE=.
#!/bin/bash
export SDL_INCLUDE=/usr/include/SDL
set -o verbose
gcc -c fvm.c -o fvm.o -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99 
gcc -c fvm/error.c -o error.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -c fvm/cpu/mem/memory.c -o mem.o -I$FVM_INCLUDE -Wall -pedantic -std=gnu99
gcc -c fvm/rom/rom.c -o rom.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -c fvm/fcall/fcall.c -o fcall.o -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -c fvm/sdl.c -o sdl.o -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -c fvm/bitutils.c -o bitutils.o -Wall -Wextra -pedantic -std=gnu99
gcc -c fvm/cpu/cpu.c -I$FVM_INCLUDE -I$SDL_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -o fvm.out fvm.o error.o mem.o rom.o fcall.o sdl.o bitutils.o cpu.o -lSDL -lSDL_ttf
# Remove all object files
rm *.o
echo 'FVM Compilation Complete.'
