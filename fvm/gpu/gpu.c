#include <stdint.h>
#include <stdlib.h>
#include <fvm/cpu/cpu.h>
#include <fvm/gpu/gpu.h>
#include <fvm/gpu/opcodes.h>
#include <fvm/sdl.h>
GL_SURFACE_t* tempsdl_image;
/* GPU of the FVM Machine */
int vpu_emulate_instruction(uint32_t* memory, int ip)
{
	switch(memory[ip])
	{
		case VPU_LOADBITMAP:
			tempsdl_image = FVM_SDL_LoadBMP(memory[(memory[ip+1])]);
			FVM_SDL_updatedisplay(tempsdl_image);
			SDL_FreeSurface(tempsdl_image);
			return 2;
		case VPU_DISPLAY_PIXEL:
			display_pixel(memory[ip+1], memory[ip+2], memory[ip+3]);
			return 4;
		
	}
}
