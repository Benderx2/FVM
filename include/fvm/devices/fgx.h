#ifndef __FGX_H
#define __FGX_H
#include <stdint.h>
#include <fvm/cpu/ports.h>
#define FGX_SET_RESOLUTION 0x47E3
void FGX_refresh(FVM_PORT_t* IOADDR_SPACE);
void display_pixel(int x, int y, uint32_t pixel);
#endif
