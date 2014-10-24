#include <stdio.h>
#include <stdlib.h>
#include <fvm/error.h>
#ifdef __USE_GRAPHICS
#include <SDL.h>
#endif
void FVM_EXIT(int ERR_CODE)
{
	printf("\nFVM is exitting with status: [%d]\n", ERR_CODE);
	#ifdef __USE_GRAPHICS
	SDL_quit();
	#endif
	exit(ERR_CODE);
}
