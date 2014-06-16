//! Dissassembler for Flouronix
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fvm/opcodes.h>
#include <rom.h>
#define MIN_ARGS 3
#define FVM_DISASM_VER "0.1.7"
int main(int argc, const char* argv[])
{
	if (argc < MIN_ARGS)
	{
		printf("\nFVM Disassembler Version: %s", FVM_DISASM_VER);
		printf("\nUsage: fdisasm [Size of ROM Image] [ROM Image] [Output Source File]");	
		exit(1);
	}
	uint32_t ROM_SIZE = atoi(argv[1]);
	const char* ROM_NAME = argv[2];
	const char* OUTPUT_SOURCE_NAME = argv[3];
	int32_t* PhysicalMEM = (int32_t*)malloc(ROM_SIZE);
	FILE *in = loadrom(ROM_NAME, PhysicalMEM, ROM_SIZE);
	if (in == NULL)
	{
		printf("\n>>>ROM Image Not Found");	
		exit(1);
	}
	uint32_t ip = 0;
	uint32_t end_found = 0;
	FILE *out = fopen(OUTPUT_SOURCE_NAME, "w+b");
	//! Add a include 'fvm.inc'!
	fprintf(out, "\ninclude 'fvm.inc'");
	fprintf(out, "\nuse32");
	fprintf(out, "\norg 0");
	fprintf(out, "\nalign 4");
	while(end_found == 0)
	{
		switch(PhysicalMEM[ip])
		{
			case FVM_END:
				end_found = 1;
				break;
			case FVM_SLP:
				fprintf(out, "\nslp");
				ip++;
				break;
			case FVM_EXT:
				fprintf(out, "\nexit");
				ip++;
				break;
			case FVM_LD0:
				if(PhysicalMEM[ip+1] == OPCODE_R1)
				{
					fprintf(out, "\nld0 R1");
				}
				else {
					fprintf(out, "\nld0 %d", PhysicalMEM[ip+1]);
				}
				ip += 2;
				break;
			case FVM_FCALL:
				fprintf(out, "\nfcall %d", PhysicalMEM[ip+1]);
				ip += 2;
				break;
			case FVM_LD1:
				if(PhysicalMEM[ip+1] == OPCODE_R0)
				{
					fprintf(out, "\nld1 R0");
				}
				else {
					fprintf(out, "\nld1 %d", PhysicalMEM[ip+1]);
				}
				ip += 2;
				break;
			case FVM_JTX:
				fprintf(out, "\njtx %d", PhysicalMEM[ip+1]);
				ip += 2;
				break;
			case FVM_RET:
				fprintf(out, "\nfret");
				ip++;
				break;
			case FVM_PUSH:
				if(PhysicalMEM[ip+1] == OPCODE_R0)
				{
					fprintf(out, "\npush R0");
				}
				else if (PhysicalMEM[ip+1] == OPCODE_R1)
				{
					fprintf(out, "\npush R1");
				}
				else {
					fprintf(out, "\npush %d", PhysicalMEM[ip+1]);
				}
				ip += 2;
				break;
			case FVM_POPR:
				if (PhysicalMEM[ip+1] == OPCODE_R0)
				{
					fprintf(out, "\npopr R0");
				}
				else if (PhysicalMEM[ip+1] == OPCODE_R1)
				{
					fprintf(out, "\npopr R1");
				}
				else {
					fprintf(out, "\npopr INVALID");
				}
				ip += 2;
				break;
			case FVM_DEBUG:
				fprintf(out, "\ndebug");
				ip++;
				break;
			case FVM_LD1FA0:
				fprintf(out, "\nld1fa0");
				ip++;
				break;
			case FVM_CALL:
				fprintf(out, "\nccall %d", PhysicalMEM[ip+1]);
				ip += 2;
				break;
			case FVM_CMPV:
				if (PhysicalMEM[ip+1] == OPCODE_R1)
				{
					fprintf(out, "\ncmpv R1, %d", PhysicalMEM[ip+1+1]);
				}
				else if (PhysicalMEM[ip+1] == OPCODE_R0)
				{
					fprintf(out, "\ncmpv R0, %d", PhysicalMEM[ip+1+1]);
				}
				ip += 3;
				break;
			case FVM_JEX:
				fprintf(out, "\njex %d", PhysicalMEM[ip+1]);
				ip += 2;
				break;
			case FVM_JGX:
				fprintf(out, "\njgx %d", PhysicalMEM[ip+1]);
				ip += 2;
				break;
			case FVM_JLX:
				fprintf(out, "\njlx %d", PhysicalMEM[ip+1]);
				ip += 2;
				break;
			case FVM_ST1TA0:
				fprintf(out, "\nst1ta0");
				ip++;
				break;
			default:
				fprintf(out, "\ndd %d", PhysicalMEM[ip]);
				ip++;
				break;
		}
	}
}
