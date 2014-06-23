#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fv11.h"
int main(int argc, const char* argv[])
{
	printf("FVM ROM Dump Tool\n");
	const char* ROMFILE = argv[1];
	FILE *p = fopen(ROMFILE, "r+b");
	if(p == NULL)
	{
		printf("ROM File Not found exitting\n");
		exit(-1);	
	}
	else {
		fseek(p, 0L, SEEK_END);
		int rom_file_size = ftell(p);
		uint32_t* buffer = malloc(rom_file_size);
		fseek(p, 0L, SEEK_SET);
		printf("Size of ROM File : [%d]\n", rom_file_size);
		fread(buffer, sizeof(uint8_t), rom_file_size, p);
		/** Let's examine the ROM File **/
		FV11_HEADER_t* rom_header = (FV11_HEADER_t*)&buffer[0];
		if(rom_header->magic != FV11_MAGIC)
		{
			printf("rom_header->magic: [%d], expected [%d]\n", rom_header->magic, FV11_MAGIC);
			printf("error: given file is not a valid FV11 ROM file\n");
			exit(-1); 
		}
		else {
			printf("MAGIC Header: [0x%X]\nStart Address (Relative to 0): [0x%X]\nExpected Load Address: [0x%X]\nLength of .text section : [0x%X]\nVendor String : %s\n", rom_header->magic, rom_header->start_addr, rom_header->where_to_load, rom_header->length_of_text, rom_header->vendorstring);
		}
	}
	return 0;		
}
