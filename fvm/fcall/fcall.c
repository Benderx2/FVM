#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fvm/error.h>
#include <fvm/cpu/cpu.h>
#include <fvm/fcall/fcall.h>
#include <fvm/version.h>
#ifdef __USE_GRAPHICS
#include <fvm/sdl.h>
#endif
uint32_t retval;
uint32_t returnval;
int fcall(FVM_REG_t callnum, FVM_REG_t r1, FVM_REG_t r0, FVM_REG_t r2)
{
	if (callnum == FCALL_WRITE)
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
	else if(callnum == FCALL_READ)
	{
	#ifdef __USE_GRAPHICS
		keycode = 0;
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				FVM_EXIT(FVM_NO_ERR);
			}
			//If a key was pressed
            		else if(event.type == SDL_KEYDOWN)
            		{
				SDL_EnableUNICODE( SDL_ENABLE );
				keycode = (char)event.key.keysym.unicode;
			}
		}
		if (keycode != 0)
		{
			return FCALL_READ;
		}
		else {
			return -2;
		}
	#endif
	}
	else if (callnum == FCALL_PUTPIXEL)
	{
		FVM_SDL_putpixel(screen,r0, r1, r2);
		FVM_SDL_updatedisplay(screen);
	}
	else if (callnum == FCALL_PRINTINT)
	{
		SDL_printf(bmpfont, screen,  "%d", r0);
	}
	return F_ERR;
}

