#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fvm/cpu/cpu.h>
#include <fvm/fcall/fcall.h>
#include <fvm/version.h>
#ifdef __USE_GRAPHICS
#include <fvm/sdl.h>
#endif
int fcall(FVM_REG_t r0, FVM_REG_t r1)
{
	if (r0 == FCALL_WRITE)
		{
			#ifdef __USE_GRAPHICS
			FVM_SDL_putchar(bmpfont, screen, r1);
			FVM_SDL_updatedisplay(screen);
			#else 
			putchar(r1);
			#endif
			//putchar(r1);FVMPutchar(r1);
			//! Temporary buffer
			return 0;
		}
	return F_ERR;
}

