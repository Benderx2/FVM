# Better change this to your fucking directory ok?
export FVM_INCLUDE=.
#!/bin/bash
set -o verbose
gcc -c fvm.c -o fvm.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -c fvm/error.c -o error.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -c fvm/cpu/mem/memory.c -o mem.o -I$FVM_INCLUDE -Wall -pedantic -std=gnu99
gcc -c fvm/rom/rom.c -o rom.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -c fvm/fcall/fcall.c -o fcall.o -I$FVM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -o fvm.out fvm.o error.o mem.o rom.o fcall.o
rm *.o
