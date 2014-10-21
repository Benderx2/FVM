/** FVM FGX Video Card **/
#include <fvm/version.h>
#include <fvm/devices/fgx.h>
#include <fvm/devices/ppu.h>
#include <fvm/error.h>
#include <stdint.h>
#include <fvm/sdl.h>
#include <fvm/cpu/ports.h>
void private_ppu_check(PPU_t* ppu);
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
	printf("Initializing FVM PPU\n");
	// Allocate memory for PPU
	FVM_PPU = (PPU_t*)malloc(sizeof(PPU_t));
	FVM_PPU->memory = (uint8_t*)malloc(TOTAL_PPU_MEM);
	// Set the variables
	FVM_PPU->x_res = GL_MAX_X;
	FVM_PPU->y_res = GL_MAX_Y;
	FVM_PPU->memsize = TOTAL_PPU_MEM;
	// Zero out all memory
	memset(FVM_PPU->memory, 0, FVM_PPU->memsize);
}
void write_ppu(PPU_t* ppu, uint8_t* src, int off, int len)
{
	if(off + len > ppu->memsize) { return; } 
	memcpy((void*)((uintptr_t)ppu->memory + off), src, len);
}
void read_ppu(PPU_t* ppu, void* dest, int off, int len)
{
	if(off + len > ppu->memsize) { return; }
	memcpy(dest, (void*)((uintptr_t)ppu->memory + off), len);
}
void private_ppu_check(PPU_t* ppu)
{
	ppu->x_res = GL_MAX_X;
	ppu->y_res = GL_MAX_Y;
	ppu->memsize = TOTAL_PPU_MEM;
}
void update_ppu_display(PPU_t* ppu)
{
	int buf_len = screen->pitch * screen->h;
	if(buf_len < TOTAL_PPU_MEM) { printf(" [FATAL: Current Video State cannot support PPU display\n"); FVM_EXIT(FVM_PROGRAM_ERR); }
	memset((void*)screen->pixels, 0, buf_len);
	memcpy((void*)screen->pixels, ppu->memory, TOTAL_PPU_MEM);
	//private_ppu_check(ppu);
	printf("TOTAL_PPU_MEM: %d\n", TOTAL_PPU_MEM);
	int i;
	while(i < TOTAL_PPU_MEM)
	{
		printf("%x ", ppu->memory[i]);
		i++;
	}
	
	FVM_SDL_updatedisplay(screen);
}
