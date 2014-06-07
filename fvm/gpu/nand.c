#include <fvm/gpu/nand.h>
uint32_t do_nand(uint32_t x, uint32_t y)
{
	return ~ (x & y);
}
