#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *img = NULL;

void exit_msg(char *msg) {
    printf(msg);
    exit(-1);
}

int main(int argc, char* args[]) {
    // setup SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
        exit_msg("Couldn't init SDL");

    // setup SDL window
    window = SDL_CreateWindow("SDL Examples", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
        exit_msg("Couldn't init SDL Window");

    // setup SDL Image
    if(IMG_Init(IMG_INIT_PNG) == -1)
        exit_msg("Couldn't init SDL Image");

    // load image
    img = IMG_Load("twi.png");
    if(img == NULL)
        exit_msg("Couldn't load twi.png");

    // Get window surface
    screen = SDL_GetWindowSurface(window);

    // Fill background with black
    SDL_FillRect(screen, NULL, 0x000000);

    // Blitz image onto screen
    SDL_BlitSurface(img, NULL, screen, NULL);

    // Update window
    SDL_UpdateWindowSurface(window);

    // wait 3 seconds
    SDL_Delay(3000);

    // free image
    SDL_FreeSurface(img);
    // free window
    SDL_DestroyWindow(window);

    // quite SDL
    SDL_Quit();

    return 0;
}
