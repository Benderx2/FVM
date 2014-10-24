export SDL_INCLUDE=/usr/include/SDL
gcc -shared -o test.so -fPIC chip8.c -I$SDL_INCLUDE -lSDL -lSDL_ttf -std=c99
