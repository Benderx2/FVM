#include <stdio.h>
#include <string.h>
#include <fvm/error.h>
#include <fvm/cpu/cpu.h>
#include <fvm/fv11/fv11.h>
int32_t fv11_load(FVM_BYTE_t* Memory)
{
	/** Parse the headers**/
	 FV11_HEADER_t* ROM_HEADER = ( FV11_HEADER_t*)&Memory[0];
	if(ROM_HEADER->magic != FV11_MAGIC)
	{
		printf("ERR: [FATAL] ROM doesn't match processor version.\n");
		FVM_EXIT(FVM_PROGRAM_ERR);
	}
	int32_t _start_address = ROM_HEADER->start_addr;
	int32_t _where_to_load = ROM_HEADER->where_to_load;
	int32_t _length_of_text_section = ROM_HEADER->length_of_text;
	// Do a memcpy!
	memcpy(Memory + _where_to_load, Memory + _start_address, _length_of_text_section);
	return _where_to_load / 4;
}
