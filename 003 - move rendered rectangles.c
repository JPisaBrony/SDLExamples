#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define RECT_SIZE 200
#define MOVEMENT_SPEED 10

SDL_Event event;
SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Rect rect;
int x_pos, y_pos;

void exit_msg(char *msg) {
    printf(msg);
    exit(-1);
}

void cleanup() {
    // free window
    SDL_DestroyWindow(window);

    // quite SDL
    SDL_Quit();
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
    x_pos = SCREEN_WIDTH / 2 - RECT_SIZE / 2;
    y_pos = SCREEN_HEIGHT / 2 - RECT_SIZE / 2;
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = RECT_SIZE;
    rect.h = RECT_SIZE;

    while(1) {
        // check for pending events
        while(SDL_PollEvent(&event)) {
            // quit was requested
            if(event.type == SDL_QUIT) {
                cleanup();
                return 0;
            // keyboard button was hit
            } else if (event.type == SDL_KEYDOWN) {
                // check which key was hit
                switch(event.key.keysym.sym) {
                    // quit
                    case 'q':
                        cleanup();
                        return 0;
                    // move left
                    case 'a':
                        x_pos -= MOVEMENT_SPEED;
                        break;
                    // move right
                    case 'd':
                        x_pos += MOVEMENT_SPEED;
                        break;
                    // move down
                    case 's':
                        y_pos += MOVEMENT_SPEED;
                        break;
                    // move up
                    case 'w':
                        y_pos -= MOVEMENT_SPEED;
                        break;
                }
            }
        }

        // set rectangle to proper position
        rect.x = x_pos;
        rect.y = y_pos;

        // Get window surface
        screen = SDL_GetWindowSurface(window);

        // Fill background with black
        SDL_FillRect(screen, NULL, 0x000000);

        // Fill rectangle with white
        SDL_FillRect(screen, &rect, 0xFFFFFF);

        // Update window
        SDL_UpdateWindowSurface(window);
    }

    return 0;
}
