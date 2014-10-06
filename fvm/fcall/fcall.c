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
extern FVM_REGISTERS_t* CPU_regs;
uint32_t retval;
uint32_t returnval;
union floatint {
	int32_t i;
	float f;
};
FILE* tempfile;
void* ptr;
char* file_string;
uintptr_t intptr;
union floatint temp;
int fcall(FVM_REG_t callnum, FVM_REG_t r1, FVM_REG_t r0, FVM_REG_t r2, uint8_t* Memory)
{
  	switch (callnum)
	{
		case FCALL_WRITE:
			#ifdef __USE_GRAPHICS
			FVM_SDL_putchar(bmpfont, screen, r1);
			FVM_SDL_updatedisplay(screen);
			#else 
			putchar(r1);
			#endif
			//putchar(r1);FVMPutchar(r1);
			//! Temporary buffer
			return 0;
		
		case FCALL_READ:	
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
		case FCALL_PUTPIXEL:
			FVM_SDL_putpixel(screen,r0, r1, r2);
			FVM_SDL_updatedisplay(screen);
	
		case FCALL_PRINTINT:
			SDL_printf(bmpfont, screen,  "%d", r1);
			FVM_SDL_updatedisplay(screen);
		case FCALL_PRINTFLOAT:
			temp.f = 0.0f;
			temp.i = r1;
			SDL_printf(bmpfont, screen, "%f", temp.f);
			FVM_SDL_updatedisplay(screen);
		case FCALL_FOPEN:
			file_string = (char*)(Memory + CPU_regs->r0);
			tempfile = fopen(file_string, "r+w");
			CPU_regs->r0 = (uintptr_t)tempfile;
			return 0;	
		case FCALL_FREAD:
			ptr = (void*)(Memory + CPU_regs->r2);
			intptr = (uintptr_t)CPU_regs->r0;
			tempfile = (FILE*)intptr;
			CPU_regs->r1 = fread(ptr, CPU_regs->r1, sizeof(uint8_t), tempfile); 
			printf("fread() Requested by program, ptr_address = %p, size = %x\n", ptr, CPU_regs->r1);
			return 0;
		default:
			return F_ERR;
	}
}

