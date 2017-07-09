#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define FONT_SIZE 50

SDL_Event event;
SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
TTF_Font *font = NULL;
SDL_Surface *text = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *screen_texture = NULL;
SDL_Color text_color;
SDL_Rect text_pos;
int i, j;

void exit_msg(char *msg) {
    printf(msg);
    exit(-1);
}

void cleanup() {
    // free image
    SDL_FreeSurface(screen);
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
    
    // setup SDL TTF
    if(TTF_Init() == -1)
        exit_msg("Couldn't init SDL TTF");
    
    // open font
    font = TTF_OpenFont("FreeMonoBold.ttf", FONT_SIZE);
    if(font == NULL)
        exit_msg("Failed to open font");
    
    // set text position
    text_pos.x = 0;
    text_pos.y = 0;
    
    // set text color to white
    text_color.r = 0xFF;
    text_color.g = 0xFF;
    text_color.b = 0xFF;
    text_color.a = 0xFF;

    // create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // create screen surface
    screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    // create screen texture
    screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    
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
        
        // create text with the font and color
        text = TTF_RenderText_Solid(font, "Twilight Sparkle is best pony", text_color);
        // blit the text to the screen
        SDL_BlitSurface(text, NULL, screen, &text_pos);
        // free the text to prevent memory leaks
        SDL_FreeSurface(text);
        
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
