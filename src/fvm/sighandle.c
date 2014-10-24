#include <stdio.h>
#include <stdlib.h>
#include <fvm/sighandle.h>
void SIGSEGV_handler(int signum)
{
	printf("SIGSEGV Caught()!\n");
	printf("This is caused due to invalid memory access by the Emulator. Please check if you're using more memory than you should or it's a bug with the VM!\nReport it to github.com/Benderx2/FVM\n");
	printf("SIGNUM: %d\n", signum);
	exit(1);
}
void SIGILL_handler(int signum)
{
	printf("SIGILL caught()!\n");
	printf("This is caused because the emulator executed an invalid instruction.\nThis means that the emulator is f**king BUGGED. Report it or be prepared to go to hell.\n");
	printf("SIGNUM: %d\n", signum);
	exit(1);
}
