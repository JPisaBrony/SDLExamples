#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define rmask 0x000000FF
#define gmask 0x0000FF00
#define bmask 0x00FF0000
#define amask 0xFF000000

SDL_Event event;
SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *colored_surface = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *screen_texture = NULL;
int i, j, alpha;

void exit_msg(char *msg) {
    printf(msg);
    exit(-1);
}

void cleanup() {
    // free image
    SDL_FreeSurface(screen);
    // free colored surface
    SDL_FreeSurface(colored_surface);
    // free image texture
    SDL_DestroyTexture(screen_texture);
    // free renderer
    SDL_DestroyRenderer(renderer);
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

    // create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // create screen surface
    screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, rmask, gmask, bmask, amask);
    // create screen texture
    screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    // create temporary surface for colors
    colored_surface  = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, rmask, gmask, bmask, amask);
    // start alpha at 0
    alpha = 0;
    
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
                }
            }
        }
        
        // fill temporary surface with blue and an alpha of 100%
        SDL_FillRect(colored_surface, NULL, 0xFF0000FF);
        // copy the temporary surface to the actually screen
        SDL_BlitSurface(colored_surface, NULL, screen, NULL);
        
        // fill temporary surface with white and an alpha of 50%
        SDL_FillRect(colored_surface, NULL, 0x80FFFFFF);
        // copy the temporary surface to the actually screen
        SDL_BlitSurface(colored_surface, NULL, screen, NULL);
        
        // fill temporary surface with black
        SDL_FillRect(colored_surface, NULL, 0xFF000000);
        // set the alpha value
        SDL_SetSurfaceAlphaMod(colored_surface, alpha);
        // copy the temporary surface to the actually screen
        SDL_BlitSurface(colored_surface, NULL, screen, NULL);
        
        // increment the alpha value to have a fading effect
        alpha += 5;
        // check if we hit the max value and reset if needed
        if(alpha > 255)
            alpha = 0;
        
        // update screen texture
        SDL_UpdateTexture(screen_texture, NULL, screen->pixels, screen->pitch);
        // clear renderer
        SDL_RenderClear(renderer);
        // copy image into renderer to be rendered
        SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
        // render image
        SDL_RenderPresent(renderer);
     }

    return 0;
}
