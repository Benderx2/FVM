#include <stdio.h>
#include <stdlib.h>
#include <fvm/error.h>
#include <fvm/rom/rom.h>
//! Load a  ROM disk image into memory
int load_disk_image(const char* ROMFILE, void* addr, uint32_t i_mem)
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
	printf("Size of ROM Disk File : [%d]\n", rom_file_size);
	//! Is size of ROM larger than available memory?
	if (rom_file_size > i_mem)
	{
		//! Yes. Exit
		FVM_EXIT(FVM_LARGE_ROM);
	}
	printf("ROM Disk Address to be loaded at : [%p]\n", (void*) addr);
	printf("Reading ROM Image......\n");
	//! read the file
	unsigned int read = fread(addr, sizeof(uint8_t), rom_file_size, p);
	if (read < rom_file_size)
	{
		printf("WARNING: fread() returns: [%d], when expected [%d]", read, rom_file_size);
	}
	printf("ROM Reading Done.\n");
	return 0;
}
