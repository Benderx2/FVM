#include <stdio.h>
#include <stdint.h>
#include <SDL_ttf.h>
#include "fvm_shared.h"
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination);
// This is a shared object which is written in C. 
// We'll call this from our VM!
SDL_Color textColor = { 255, 255, 255 };
uint32_t test_function(void* arg)
{
	SDL_Surface* bmp;
	struct SDL_Rect Temp;
	VM_API.VM_set_resolution(1024, 768, 32);
	SDL_Surface* VM_Screen = VM_API.VM_get_surface();
	bmp = SDL_LoadBMP("./lol.bmp");
	SDL_BlitSurface(bmp, NULL, VM_Screen, NULL);
	VM_API.VM_printf("Test function!\n");
	VM_API.VM_printf("Hey there! pi = %f", 3.14159265f); 	
	TTF_Init();
	TTF_Font* font = TTF_OpenFont( "/usr/share/fonts/myfonts/Minecraftia.ttf", 38 );
	SDL_Surface* message = TTF_RenderText_Solid( font, "Hello Big World!", textColor );
	apply_surface( 0, 150, message, VM_Screen );
	font = TTF_OpenFont( "/usr/share/fonts/myfonts/Minecraftia.ttf", 26 );
	message = TTF_RenderText_Solid( font, "Hello Small World!", textColor );
	apply_surface( 0, 210, message, VM_Screen );
	//Update Screen 
	SDL_Flip(VM_Screen);
	return 0;
}
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, NULL, destination, &offset );
}

