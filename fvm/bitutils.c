#include <stdint.h>
#include <fvm/bitutils.h>
// Some bit shit
uint32_t setbit32(uint32_t integer, int num)
{
	// Do a BITWISE-OR
	integer |= 1 << num;
	// Done.
	return integer;
}
uint32_t clearbit32(uint32_t integer, int num)
{
	// Do a BITWISE-AND
	integer &= ~(1 << num);
	return integer;
}
uint32_t togglebit32(uint32_t integer, int num)
{
	// Do a BITWISE-XOR
	integer ^= 1 << num;
	return integer;
}
uint32_t getbit32(uint32_t integer, int num)
{
	// Do a Bit-wise AND
	uint32_t bit = integer & (1 << num);
	return bit;
}

