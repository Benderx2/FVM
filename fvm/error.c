#include <stdio.h>
#include <stdlib.h>
void FVM_EXIT(int ERR_CODE)
{
	printf("\nFVM is exitting with status: [%d]\n", ERR_CODE);	
	exit(ERR_CODE);
}
