/** FVM FGX Video Card **/
#include <fvm/devices/fgx.h>
#include <fvm/cpu/ports.h>
void FGX_refresh(FVM_PORT_t* IOADDR_SPACE[0xFF])
{
	/** Usually called after every 10 CPU Cycles **/
	if(IOADDR_SPACE[0x3B].in == FGX_SET_RESOLUTION)
	{
		VM_set_resolution(IO_ADDR_SPACE[0x3D].in, IO_ADDR_SPACE[0x3E].in, IO_ADDR_SPACE[0x3F].in);
		IO_ADDR_SPACE[0x3C].out = 0x3FF; /** Send SET_RESOLUTION command to port 0x3C **/
	}
	else {
		return;
	}
	
}
