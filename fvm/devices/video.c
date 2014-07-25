/** FVM FGX Video Card **/
#include <fvm/version.h>
#include <fvm/devices/fgx.h>
#include <stdint.h>
#include <fvm/sdl.h>
#include <fvm/cpu/ports.h>
void FGX_refresh(FVM_PORT_t* IO_ADDR_SPACE)
{
	printf("FGX_INTERRUPT: IN = %d, GL_WIDTH : %d, GL_HEIGHT : %d, GL_COLOR : %d\n", IO_ADDR_SPACE[0x3B].in, IO_ADDR_SPACE[0x3D].in, IO_ADDR_SPACE[0x3E].in, IO_ADDR_SPACE[0x3F].in);
	if(IO_ADDR_SPACE[0x3B].in == FGX_SET_RESOLUTION)
	{
		/** Reinitialize graphics with resolution **/
		FVM_SDL_init(IO_ADDR_SPACE[0x3D].in, IO_ADDR_SPACE[0x3E].in, IO_ADDR_SPACE[0x3F].in);
		IO_ADDR_SPACE[0x3C].out = 0x3FF; /** Send SET_RESOLUTION command to port 0x3C **/
		IO_ADDR_SPACE[0x3B].in = 0;
	}
	else {
		return;
	}
	
}
