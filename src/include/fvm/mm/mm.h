#ifndef __MM_H
#define __MM_H
#define T_MEM_SIZE 8192
#include <stdint.h>
#include <stdbool.h>
typedef struct MemEntry {
	uint8_t* memory;	
	uint32_t stdsize;
	uint32_t start;
	uint32_t end;
	bool used;
} MemEntry_t;
typedef struct MemReturn {
	uint8_t* address;
	int block;
} MemReturn_t;
int mm_init(uint8_t* memory, int size);
MemReturn_t* mm_allocate_one(void);
int mm_free(MemReturn_t* freeobj);
uint32_t return_size(void);
#endif
