export SDL_INCLUDE=/usr/include/SDL
gcc -shared -o test.so -fPIC test.c -I$SDL_INCLUDE -lSDL 