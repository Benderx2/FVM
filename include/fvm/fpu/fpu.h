#ifndef __FPU_H
#define __FPU_H
#include <stdint.h>
#include <fvm/cpu/opcodes.h>
void pushfloat(int32_t* mem, int32_t sp, float value);
float do_sin_x(int32_t IEEE754Encoded_value);
float do_cos_x(int32_t IEEE754Encoded_value);
float do_pow_x(int32_t numIEEE754, int32_t powIEEE754);
float do_abs_x(int32_t numIEEE754);
float do_asin_x(int32_t numIEEE754);
float do_acos_x(int32_t numIEEE754);
float do_atan_x(int32_t numIEEE754);
float do_arithmetic_operation(int32_t IEEE7541, int32_t IEEE7542, int operation);
#endif

