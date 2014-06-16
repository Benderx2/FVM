export FVM_DISASM_INCLUDE=.
gcc -c fdisasm.c -o fdisasm.o -I$FVM_DISASM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -c rom.c -o rom.o -I$FVM_DISASM_INCLUDE -Wall -Wextra -pedantic -std=gnu99
gcc -o fdisasm.out rom.o fdisasm.o
