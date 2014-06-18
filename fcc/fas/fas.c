// Flouronix Assembler
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h> /* For ERRNO */
#include "cpu/opcodes.h"
char get_ch();
char* token;
int grab_token();
uint32_t get_opcode();
// define size as constant
const int BUFF_SIZE = 256;
FILE *source_FILE, *output_FILE;
const char* source_filename;
const char* output_filename;
int line;
/* Buffer for receiving characters */
int char_recv_buf;

// Instructions...
const int total_opcodes = 31;
const int total_regs = 7;
char* instructions[] =
{
			"ld0", "ld1", "ld2", "ld3", "ld4", "ld5", "ld12", "jmp", "je", "jg", "jl", "call", "ret",
			"fcall", "push", "popr", "ld1fa0", "st1ta0", "cmp", "debug", "lith", "int", "in0", "out0",
			"xor", "incr", "decr", "mul", "div", "exit", "slp"
};
// Registers
char* regs[] =
{
			"r0", "r1", "r2", "r3", "r4", "r5", "r12"
};
// Opcodes (in the same order)
uint32_t opcodes[] =
{
		FVM_LD0, FVM_LD1, FVM_LD2, FVM_LD3, FVM_LD4, FVM_LD5, FVM_LD12, FVM_JTX, FVM_JEX, FVM_JGX, FVM_JLX,
		FVM_CALL, FVM_RET, FVM_FCALL, FVM_PUSH, FVM_POPR, FVM_LD1FA0, FVM_ST1TA0, FVM_CMPV, FVM_DEBUG, FVM_LITH,
		FVM_INT, FVM_IN0, FVM_OUT0, FVM_XOR, FVM_INCR, FVM_DECR, FVM_MUL, FVM_DIV, FVM_EXT, FVM_SLP	
};
// Register Markers
uint32_t opcode_regs[] =
{
		OPCODE_R1, OPCODE_R2, OPCODE_R3, OPCODE_R4, OPCODE_R5, OPCODE_R12
};
int main(int argc, const char* argv[])
{
		if(argc < 2)
		{
			printf("No enough arguments provided\n");
			printf("fas - FVM Assembler, Usage: \n");
			printf("fas [source] [rom output]\n");
			exit(1);
		}
		// Grab the pointers of the filenames passed by the shell.
		source_filename = argv[1];
		output_filename = argv[2];
		// Open the source File for reading and in binary mode
		source_FILE = fopen(source_filename, "r+b");
		if (source_FILE == NULL)
		{
				printf("Error while writing/reading files\n");
				printf("<errno>: %d\n", errno);
				printf("Exitting....\n");
				exit(1);
		}
		token = malloc(256);
		grab_token();
		printf("%s", token);
		return 0;
}
// Grab a character from the file
char get_ch()
{
	char c = fgetc(source_FILE);
	c = tolower(c);
	return c;
}
// Reset position in file
void reset_pos()
{
	fseek(source_FILE, 0L, SEEK_SET);
}
int grab_token()
{
    char a;
    int i = 0;
 
    while((a = get_ch())!=EOF) {
        if(a == ' ' || a == '\t' || a == '\r' || a == '\n') // this part can be converted to macro
            continue;
        break;
    }
    if(a==EOF) {
        token[0]=0;
        // maybe some error handling
        return;
    }
 
    while((a = get_ch())!=EOF) {
        if(a == ' ' || a == '\t' || a == '\r' || a == '\n')
            break;
        if(i<BUFF_SIZE-2) // BUFF_SIZE-1 is reserved for termination
            token[i++]=a;
        else {
		return -1;
        }
    }
    token[i]=0;
    return 0;
}
/** Simple Parser **/
uint32_t get_opcode()
{
	int c, match =0;
	/** Grab a token from the file **/
	grab_token();
	/** Compare it **/
	while(c <= total_opcodes)	
	{
			match = strcmp(instructions[c], token);
			c++;
	}
	if(match == 0)
	{
		// Yep it's an instruction
		return opcodes[c];
	}
	/** Could be a register **/
	else if(match != 0) {
		c = 0;
		match = 1;
		while(c <= total_regs)
		{
			match = strcmp(regs[c], token);
			c++;
		}
		if(match == 0)
		{
			return opcode_regs[c];
		}
	}
	else {
		/** Return Bitches, it's a string or a literal, the token is safely stored in the buffer. **/
		return -1;
	}
}


