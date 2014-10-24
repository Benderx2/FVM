#ifndef __PPU_H
#define __PPU_H
#define TOTAL_PPU_MEM 2560*480
typedef struct sPPU {
	int memsize;
	uint8_t* memory; // 16K of Memory
	int x_res;
	int y_res;
} PPU_t;
extern PPU_t* FVM_PPU;
void read_ppu(PPU_t* ppu, void* dest, int off, int len);
void update_ppu_display(PPU_t* ppu);
void write_ppu(PPU_t* ppu, uint8_t* src, int src_off, int off, int len);
void init_ppu(void);
#endif
