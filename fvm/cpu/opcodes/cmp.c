#include <fvm/cpu/registers.h>
#include <fvm/cpu/cpu.h>
int cmp(FVM_REG_t op1, FVM_REG_t op2)
{
	if(op1 == op2)
	{
		return 0;
	}
	if (op1 < op2)
	{
		return 1;
	}
	if (op1 > op2)
	{	
		return 2;
	}

}
