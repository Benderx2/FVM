#include <stdio.h>
#include <stdlib.h>
#include <fvm/error.h>
#include <fvm/rom/rom.h>
//! Load a ROM into memory
int loadrom(const char* ROMFILE, void* addr, uint32_t total_mem)
{
	uint32_t rom_file_size;
	//! open the file in Read + Binary mode
	FILE *p = fopen(ROMFILE, "r+b");
	if (p == NULL)
	{
		FVM_EXIT(FVM_NO_ROM);
	}
	//! Get File Size
	fseek(p, 0L, SEEK_END);
	rom_file_size = ftell(p);
	fseek(p, 0L, SEEK_SET);
	printf("\nSize of ROM File : [%d] and Virtual Machine Memory : [%d]", rom_file_size, total_mem);
	//! Is size of ROM larger than available memory?
	if (rom_file_size > total_mem)
	{
		//! Yes. Exit
		FVM_EXIT(FVM_LARGE_ROM);
	}
	printf("\nROM Address to be loaded at : [%p]", (void*) addr);
	printf("\nReading ROM Image......");
	//! read the file
	unsigned int read = fread(addr, sizeof(uint8_t), rom_file_size, p);
	if (read < rom_file_size)
	{
		printf("WARNING: fread() returns: [%d], when expected [%d]", read, rom_file_size);
	}
	printf("\nROM Reading Done.");
	return 0;
}
