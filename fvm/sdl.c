/** SDL Interface for FVM **/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL.h>
#include <fvm/sdl.h>
#include <fvm/error.h>
int screen_x = 0;
int screen_y = 0;
GL_SURFACE_t* screen;
GL_SURFACE_t* bmpfont;
SDL_Color COLOR = { 255, 255, 255, 60 };
void FVM_SDL_init(GL_WIDTH_t width, GL_HEIGHT_t height, GL_DEPTH_t color)
{
	//! Init everything.
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(width, height, color, SDL_SWSURFACE);
}
GL_SURFACE_t* FVM_SDL_loadbmp(const char* FILENAME)
{
	GL_SURFACE_t* Image = SDL_LoadBMP(FILENAME);
	GL_SURFACE_t* OptimizedImage = NULL;
	if (Image != NULL)
	{
		OptimizedImage = SDL_DisplayFormat(Image);
		SDL_FreeSurface(Image);
		return OptimizedImage;
	}
	return NULL;
}
void FVM_SDL_updatedisplay(GL_SURFACE_t* SURFACE)
{
	 SDL_BlitSurface(SURFACE, NULL, screen, NULL); 
	 SDL_Flip(screen);
}
void FVM_SDL_delay(uint32_t time)
{
	SDL_Delay(time);
}
void FVM_SDL_blitsurface(int x, int y, GL_SURFACE_t* source, GL_SURFACE_t* dest)
{
	GL_RECT_t NewRect;
	NewRect.x = x;
	NewRect.y = y;
	SDL_BlitSurface(source,NULL,dest, &NewRect);
}
void FVM_SDL_setwincaption(const char* caption)
{
	SDL_WM_SetCaption(caption, NULL);
}
void FVM_SDL_putentry(GL_SURFACE_t* font, GL_SURFACE_t* dest, int x, int y, unsigned char c)
{
        static SDL_Rect font_rect, dest_rect;
       	int indice = c - 32;
	if (c >= 'a' && c <= 'z')
	{
		char n = toupper(c);
		c = n;
		indice = c - 32;
	}
	else if(c < 32 || c > 109) {
		return;
	}
        font_rect.x = indice *  (font->w / 77);
        font_rect.y = 0;
        font_rect.w = font->w / 77;
        font_rect.h = font->h;
        dest_rect.x = x;
        dest_rect.y = y;
        dest_rect.w = font->w / 77;
        dest_rect.h = font->h;

        SDL_BlitSurface(font, &font_rect, dest, &dest_rect);
}
void FVM_SDL_putchar(GL_SURFACE_t* font, GL_SURFACE_t* dest, unsigned char c)
{	
	FVM_SDL_putentry(font, dest, screen_x, screen_y, c);
	screen_x += 10;
	if (screen_x >= 320)
	{
		screen_y += 10;
	}
}
void FVM_SDL_putstring(GL_SURFACE_t* font, GL_SURFACE_t* dest, const char* string)
{
	unsigned int i = 0;
	while( i <= strlen(string))
	{
		FVM_SDL_putchar(font, dest, string[i]);
		i++;
	}
}
