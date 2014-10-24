#include <stdint.h>
#include <fvm/gc/objects.h>
void pushObj(Object* Obj, uint32_t* stack, uint32_t stackptr)
{
	stack[stackptr-1] = Obj->value;
	stack[stackptr-2] = Obj->type;
}

