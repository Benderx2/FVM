#include <float.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <fvm/fpu/fpu.h>
#include <fvm/tweaks.h>
union FloatAndInt retval;
union FloatAndInt* returnfloatunion (int32_t val);
union FloatAndInt* returnintunion(float val);
union FloatAndInt {
	int32_t i;
	float f;
};
union FloatAndInt* returnfloatunion (int32_t val)
{
	retval.i = val;
	return &retval;
}
union FloatAndInt* returnintunion(float val)
{
	retval.f = val;
	return &retval;
}
void pushfloat(int32_t* mem, int32_t sp, float value)
{
	union FloatAndInt* temp = returnintunion(value);
	mem[sp] = temp->i;
	return;
}
float do_sin_x(int32_t IEEE754Encoded_value)
{
	union FloatAndInt* temp = returnfloatunion(IEEE754Encoded_value); 
	temp->f = sin(temp->f);
	return temp->f;
} 
float do_cos_x(int32_t IEEE754Encoded_value)
{
	union FloatAndInt* temp = returnfloatunion(IEEE754Encoded_value); 
	temp->f = cos(temp->f);
	return temp->f;
} 
float do_pow_x(int32_t numIEEE754, int32_t powIEEE754)
{
	union FloatAndInt* temp = returnfloatunion(numIEEE754);	
	float a = temp->f;
	temp = returnfloatunion(powIEEE754);
	float b = temp->f;
	printf("FPU POW() = a : %f ^ b : %f", a , b);
	return pow(a, b);
}
float do_abs_x(int32_t numIEEE754)
{
	union FloatAndInt* temp = returnfloatunion(numIEEE754);
	return fabs(temp->f);
}
float do_arithmetic_operation(int32_t IEEE7541, int32_t IEEE7542, int operation)
{
	union FloatAndInt* temp = returnfloatunion(IEEE7541);
	float a = temp->f;
	temp = returnfloatunion(IEEE7542);
	float b = temp->f;
	switch(operation)
	{
		case FPU_ADD:
			return  a + b;
		case FPU_SUB:
			return a - b;
		case FPU_MUL:
			return a * b;
		case FPU_DIV:
			return a / b;
	}
	return 0;
}
