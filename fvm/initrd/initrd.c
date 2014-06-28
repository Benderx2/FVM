/** initrd - Ramdisk for FVM **/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fvm/initrd/initrd.h>
#include <fvm/error.h>
void load_file_from_disk(uint8_t* mem, const char* file_name, uint8_t* buffer)
{
	initrd_header_t* header = (initrd_header_t*)&buffer[0];
	initrd_file_header_t* file_headers = (initrd_file_header_t*)&buffer[sizeof(initrd_header_t)];
	unsigned int i = 0;
	for(i = 0; i <= header->files; i++)
	{
		if(strcmp(file_headers[i].name, file_name) == 0)
		{
			memcpy(mem, buffer + file_headers[i].offset, file_headers[i].length);
			i = 0;
			break;
		}
		i++;
	}
	if(i != 0)
	{
		printf("#error: Requested executable not found\n");
		FVM_EXIT(FVM_ROM_ERR);
	}
}
