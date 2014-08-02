#include <stdio.h>
#include <stdint.h>
#include "fvm_shared.h"
// This is a shared object which is written in C. 
// We'll call this from our VM!
uint32_t test_function(void* arg)
{
	VM_API.VM_printf("Test function!\n");
	VM_API.VM_printf("Hey there! pi = %f", 3.14159265f);
	struct SDL_Rect Temp;
	VM_API.VM_set_resolution(1024, 768, 32);
	SDL_Surface* VM_Screen = VM_API.VM_get_surface();
	SDL_FillRect(VM_Screen, NULL, SDL_MapRGB(VM_Screen->format, 255, 0, 0));
	SDL_Flip(VM_Screen);
	return 0;
}
