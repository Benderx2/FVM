#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fvm/cpu/cpu.h>
#include <fvm/fcall/fcall.h>
int fcall(FVM_REG_t r0, FVM_REG_t r1)
{
	if (r0 == FCALL_WRITE)
		{
			putchar(r1);
			return 0;
		}
	return F_ERR;
}

