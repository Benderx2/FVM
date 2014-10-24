#include <stdio.h>
#include <stdint.h>
#include <fvm/cpu/mem/vmm.h>
#include <fvm/error.h>
// 0x0 - 0x600 - Physical mapped to 0x600 - 0x657 - 0xa00
int32_t vmm_virtual_to_physical(V_TABLE_t* vtable, uint32_t virt_addr)
{
	int i = 0;
	while(i <= TOTAL_V_ENTRY)
	{
		if(virt_addr <= vtable->V_ENT[i].upper_limit_vaddr && virt_addr >= vtable->V_ENT[i].lower_limit_vaddr)
		{
			return (virt_addr - vtable->V_ENT[i].lower_limit_vaddr) + vtable->V_ENT[i].lower_limit_paddr;
		}
		i++;
	}
	// V_FAULT Encountered.
	return -1;
}			
