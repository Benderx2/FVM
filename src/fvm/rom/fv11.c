#include <stdio.h>
#include <string.h>
#include <fvm/error.h>
#include <fvm/tweaks.h>
#include <fvm/classloader.h>
#include <fvm/cpu/cpu.h>
#include <fvm/fv11/fv11.h>
FV11_RETURN_t returnval;
FV11_RETURN_t* fv11_load(FVM_BYTE_t* Memory, int32_t memsize)
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
	int32_t _start_of_data = ROM_HEADER->start_of_data;
	int32_t _where_to_load_data = ROM_HEADER->where_to_load_data;
	int32_t _length_of_data = ROM_HEADER->length_of_data;
	printf("Generating Executable Information....\n");
	printf("text_section (OFFSET) : 0x%x\ntext_section (IP) : 0x%x\ntext_section (LENGTH) : 0x%x\ndata_section (OFFSET) : 0x%x\ndata_section (IP) : 0x%x\ndata_section (LENGTH) : 0x%x\nbss_section (OFFSET) : 0x%x\nbss_section (LENGTH) : 0x%x\nstack_buf: 0x%x\n", _start_address, _where_to_load, _length_of_text_section, _start_of_data, _where_to_load_data, _length_of_data, ROM_HEADER->bss_start, ROM_HEADER->bss_length, ROM_HEADER->bss_length); 
	if(memsize < _where_to_load || memsize < _where_to_load_data || memsize < ROM_HEADER->stack_buf)
	{
		printf("fatal: This ROM requires more memory than provided [%d] [%d] [%d] [%d]\n", memsize, _where_to_load, _where_to_load_data, ROM_HEADER->stack_buf);
		FVM_EXIT(FVM_LESS_MEM_ERR);
	}
	// Do a memcpy!
	memcpy(Memory + _where_to_load, Memory + _start_address, _length_of_text_section);
	memcpy(Memory + _where_to_load_data, Memory + _start_of_data, _length_of_data);
	// Next set the pointer properly (currently it's relative to 0, we want it relative to memory)
	if(ROM_HEADER->isclassreq > 0) // Are classes required for this program?
	{
		// Yup! Load them!
		class_header_t* classes_required = (class_header_t*)&(Memory[ROM_HEADER->pointer_to_class_set]);
		for(int i = 0; i < ROM_HEADER->isclassreq; i++)
		{
			UNUSED(classes_required[0]);
		}	
	}
	//if(ROM_HEADER->isreloc > 0) // Does this executable have a relocation section?
	//{
	//	reloc_label_t* reloc_table = (reloc_label_t*)&(Memory[ROM_HEADER->pointer_to_reloc_function_table]);
	//	for(int i = 0; i < ROM_HEADER->isreloc; i++)
	//	{
	//		reloc_table[i].address += _where_to_load; // Set it to the load address.
	//	}
	//}
	// Zero out BSS
	memset(Memory + ROM_HEADER->bss_start, '\0', ROM_HEADER->bss_length);
	returnval.r11 = _where_to_load / 4;
	returnval.sp =  ROM_HEADER->stack_buf / 4;
	return &returnval;
}
