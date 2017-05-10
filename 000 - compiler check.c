// SDL hello world and compiler check to make sure SDL is properly installed

#include <SDL2/SDL.h>

int main(int argc, char* args[]) {
    // setup SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    // quit SDL
    SDL_Quit();
    return 0;
}
