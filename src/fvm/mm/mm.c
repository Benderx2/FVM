#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fvm/mm/mm.h>
int total_blocks = 0;
int std_size = 0; 
MemEntry_t MemoryBlock[ T_MEM_SIZE]; // 8192 blocks;
int mm_init(uint8_t* memory, int size)
{
	printf("Initalizing Memory Manager...\n");
	if(size >=  T_MEM_SIZE)
	{	
		for(int i = 0; i <=  T_MEM_SIZE; i++)
		{
			MemoryBlock[i].memory = memory;
			MemoryBlock[i].stdsize = size /  T_MEM_SIZE;
			MemoryBlock[i].start = i * (size /  T_MEM_SIZE);
			MemoryBlock[i].end = i * (size /  T_MEM_SIZE) + size / T_MEM_SIZE;
			MemoryBlock[i].used = false;
			total_blocks =  T_MEM_SIZE;
			return (size /  T_MEM_SIZE);
		}
	}
	else {
		for(int i = 0; i <= size; i++)
		{
			MemoryBlock[i].memory = memory;
			MemoryBlock[i].stdsize = 1;
			MemoryBlock[i].start = i;
			MemoryBlock[i].end = i + 1;	
			MemoryBlock[i].used = false;
			total_blocks = size;
			return 1;
		}
	}
	return 0;
}
MemReturn_t* mm_allocate_one(void)
{	
	MemReturn_t* a = malloc(sizeof(MemReturn_t));
	for(int i = 0; i <= total_blocks; i++)
	{
		if(MemoryBlock[i].used == false)
		{
			a->address = (unsigned char*)(MemoryBlock[i].memory + MemoryBlock[i].start);
			a->block = i;
			return a;
		}
	}
	printf("ERROR: mm_allocate, no memory available\n");
	return NULL;
}
int mm_free(MemReturn_t* freeobj)
{	
	if(freeobj->block <= total_blocks && freeobj->block >= 0)
	{
		MemoryBlock[freeobj->block].used = false;
		return 0;	
	}
	return -1;
}
uint32_t return_size(void)
{
	return std_size;
}
