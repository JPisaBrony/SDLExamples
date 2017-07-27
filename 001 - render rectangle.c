#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define RECT_SIZE 200

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Rect rect;

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

    // setup rectangle in center of screen
    rect.x = SCREEN_WIDTH / 2 - RECT_SIZE / 2;
    rect.y = SCREEN_HEIGHT / 2 - RECT_SIZE / 2;
    rect.w = RECT_SIZE;
    rect.h = RECT_SIZE;

    // Get window surface
    screen = SDL_GetWindowSurface(window);

    // Fill background with black
    SDL_FillRect(screen, NULL, 0x000000);

    // Fill rectangle with white
    SDL_FillRect(screen, &rect, 0xFFFFFF);

    // Update window
    SDL_UpdateWindowSurface(window);

    // wait 3 seconds
    SDL_Delay(3000);

    // free window
    SDL_DestroyWindow(window);

    // quite SDL
    SDL_Quit();

    return 0;
}
