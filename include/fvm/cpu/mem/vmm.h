/* Virtual Memory module for Flouronix */
#ifndef _VMM_H
#define _VMM_H
#define TOTAL_V_ENTRY 512
#include <stdint.h>
struct V_ENTRY
{
	/* A V entry is 32-bytes */
	// Virtual Memory in Flouronix is implemented through a set of VSMRs (Variable Sized Memory Regions)
	// For example if a programmer wants to map 0x0 - 0xFFFF to 0xFFFF - 0x1FFFE
	// they should set an entry with the following:
	// L_LIMIT_VADDR - 0xFFFF
	// U_LIMIT_VADDR - 0x1FFFE
	// L_LIMIT_PADDR - 0x0
	// U_LIMIT_PADDR - 0xFFFF
	// There are only two instructions that modify the memory LD1FA0 and ST1TA0, if
	// these are done under virtual memory mode and the system doesn't find a table mapped
	// it raises a V_FAULT handler.
	uint32_t lower_limit_vaddr; // Lower Limit of the Virtual Address Space
	uint32_t upper_limit_vaddr; // Higher Limit of the Virtual Address Space
	uint32_t lower_limit_paddr; // Lower Limit of the Physical Address Space
	uint32_t upper_limit_paddr; // Higher Limit of the Physical Address Space
};
typedef struct V_ENTRY V_ENTRY_t;
struct V_TABLE
{
	V_ENTRY_t V_ENT[TOTAL_V_ENTRY];
};
typedef struct V_TABLE V_TABLE_t;
#endif

