/** FVM FGX Video Card **/
#include <fvm/version.h>
#include <fvm/devices/fgx.h>
#include <fvm/devices/ppu.h>
#include <stdint.h>
#include <fvm/sdl.h>
#include <fvm/cpu/ports.h>
PPU_t* FVM_PPU;
void FGX_refresh(FVM_PORT_t* IO_ADDR_SPACE)
{
	//printf("FGX_INTERRUPT: IN = %d, GL_WIDTH : %d, GL_HEIGHT : %d, GL_COLOR : %d\n", IO_ADDR_SPACE[0x3B].in, IO_ADDR_SPACE[0x3D].in, IO_ADDR_SPACE[0x3E].in, IO_ADDR_SPACE[0x3F].in);
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
void init_ppu(void)
{	
	// Allocate memory for PPU
	FVM_PPU = (PPU_t*)malloc(sizeof(PPU_t));
	// Set the variables
	FVM_PPU->x_res = GL_MAX_X;
	FVM_PPU->y_res = GL_MAX_Y;
	FVM_PPU->memsize = TOTAL_PPU_MEM;
	// Zero out all memory
	memset(FVM_PPU->memory, 0, FVM_PPU->memsize);
}
void write_ppu(PPU_t* ppu, void* src, int off, int len)
{
	if(off + len > ppu->memsize) { return; } 
	memcpy((void*)((uintptr_t)ppu->memory + off), src, len);
}
void read_ppu(PPU_t* ppu, void* dest, int off, int len)
{
	if(off + len > ppu->memsize) { return; }
	memcpy(dest, (void*)((uintptr_t)ppu->memory + off), len);
}
void update_ppu_display(PPU_t* ppu)
{
	GL_SURFACE_t *temp = IMG_Load_RW(SDL_RWFromMem(ppu->memory, ppu->memsize), 1);
	if(temp == NULL) {  printf("IMG_Load_RW: %s\n", IMG_GetError()); }
	FVM_SDL_updatedisplay(temp);
}
