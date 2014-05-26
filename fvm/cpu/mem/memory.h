//! Memory.h -- Definitions for Memory Crap
#ifndef __FVM_MEMORY_H
#define __FVM_MEMORY_H
#include <stdint.h>
typedef uint16_t* FVM_ADDR_SIZE_t;
uint16_t* virtual_to_physical(uint16_t MEM_LOC, uint16_t* MEMORY_BUFFER);
#endif
