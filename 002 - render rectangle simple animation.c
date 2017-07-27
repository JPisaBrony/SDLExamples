#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Rect rect;
Uint32 rect_color;
int rect_size = 0;
int run_times = 0;

void exit_msg(char *msg) {
    printf(msg);
    exit(-1);
}

int main(int argc, char* args[]) {
    // seed random number generator
    srand(time(NULL));

    // setup SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
        exit_msg("Couldn't init SDL");

    // setup SDL window
    window = SDL_CreateWindow("SDL Examples", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
        exit_msg("Couldn't init SDL Window");

    // Get window surface
    screen = SDL_GetWindowSurface(window);

    // get a random color
    rect_color = rand();

    while(1) {
        // check if size is larger than the screen
        if(rect_size > 1000) {
            // reset size
            rect_size = 0;
            // get a random color
            rect_color = rand();
        }
        rect_size++;

        // set size to rectangle
        rect.x = SCREEN_WIDTH / 2 - rect_size / 2;
        rect.y = SCREEN_HEIGHT / 2 - rect_size / 2;
        rect.w = rect_size;
        rect.h = rect_size;

        // Fill background with black
        SDL_FillRect(screen, NULL, 0x000000);

        // Fill rectangle with color
        SDL_FillRect(screen, &rect, rect_color);

        // Update window
        SDL_UpdateWindowSurface(window);

        // exit condition
        // break after running 5 full times
        run_times++;
        if(run_times > 5000)
            break;
    }

    // free window
    SDL_DestroyWindow(window);

    // quite SDL
    SDL_Quit();

    return 0;
}
