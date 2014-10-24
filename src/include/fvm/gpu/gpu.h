#ifndef __GPU_H
#define __GPU_H
#include <float.h>
#include <stdint.h>
int vpu_emulate_instruction(uint32_t* memory, int ip);
#endif
