/* SDL Interface for the Flouronix VM */
#ifndef __SDL___H
#define __SDL___H
#include <stdint.h>
#include <SDL.h>
#include <SDL_keyboard.h>
#define GL_MAX_X 400
#define GL_MAX_Y 300
#define GL_COLOR 32
#define FONT_WIDTH 10
#define FONT_HEIGHT 20
#define FONT_PTSIZE 12
typedef SDL_Surface GL_SURFACE_t;
typedef SDL_Rect GL_RECT_t;
typedef SDL_Event GL_EVENT_t;
typedef const int GL_WIDTH_t;
typedef const int GL_HEIGHT_t;
typedef const int GL_DEPTH_t;
typedef int GL_CORD_t;
extern uint32_t keycode;
extern GL_SURFACE_t* screen;
extern GL_SURFACE_t* bmpfont;
extern int screen_x;
extern int screen_y;
extern GL_EVENT_t event;
void FVM_SDL_init(GL_WIDTH_t width, GL_HEIGHT_t height, GL_DEPTH_t color);
GL_SURFACE_t* FVM_SDL_loadbmp(const char* FILENAME);
void FVM_SDL_updatedisplay(GL_SURFACE_t* SURFACE);
void FVM_SDL_delay(uint32_t time);
void FVM_SDL_blitsurface(int x, int y, GL_SURFACE_t* source, GL_SURFACE_t* dest); 
void FVM_SDL_setwincaption(const char* caption);
void FVM_SDL_putentry(GL_SURFACE_t* font, GL_SURFACE_t* dest, int x, int y, unsigned char c);
void FVM_SDL_putstringat(GL_SURFACE_t* font, GL_SURFACE_t* dest, int x, int y, const char* string);
void FVM_SDL_putchar(GL_SURFACE_t* font, GL_SURFACE_t* dest, unsigned char c);
void FVM_SDL_putstring(GL_SURFACE_t* font, GL_SURFACE_t* dest, const char* string);
void SDL_printf(GL_SURFACE_t* font, GL_SURFACE_t*  dest, const char *fmt, ...);
#endif
