#include <stdint.h>
#include <stdlib.h>
#include <fvm/cpu/mem/memory.h>
uint16_t* virtual_to_physical(uint16_t MEM_LOC, uint16_t* MEMORY_BUFFER)
{
	uint16_t* a = MEM_LOC + MEMORY_BUFFER;
	return a;
}

