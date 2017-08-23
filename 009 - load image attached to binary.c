// in order to compile this file you will need to create a linkable image file by running
// ld -r -b binary -o twi.o twi.png
// the file can be compiled by running
// gcc -lSDL2 -lSDL2_image twi.o 009\ -\ load\ image\ attached\ to\ binary.c -o main
// NOTE on Windows the _binary_twi_png_start and _binary_twi_png_end
// need to be binary_twi_png_start and binary_twi_png_start (without the first underscore)

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

SDL_Event event;
SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *img = NULL;
SDL_Texture *img_texture = NULL;
SDL_Renderer *renderer = NULL;
SDL_RWops *wops = NULL;
SDL_Rect img_rect;
extern char _binary_twi_png_start[];
extern char _binary_twi_png_end[];
char *twi_png_bytes;

void exit_msg(char *msg) {
    printf(msg);
    exit(-1);
}

void cleanup() {
    // free image bytes
    free(twi_png_bytes);
    // free image
    SDL_FreeSurface(img);
    // free image texture
    SDL_DestroyTexture(img_texture);
    // free renderer
    SDL_DestroyRenderer(renderer);
    // free window
    SDL_DestroyWindow(window);
    // quite SDL
    SDL_Quit();
}

int main(int argc, char* args[]) {
    // temp pointer to iterate through binary
    char *twi_png;
    int i = 0;
    // calculate the size of the image
    unsigned int twi_img_size = (unsigned int)(_binary_twi_png_end - _binary_twi_png_start);
    // allocate the memory
    twi_png_bytes = malloc(sizeof(char) * twi_img_size);
    // iterate over the data
    for(twi_png = _binary_twi_png_start; twi_png != _binary_twi_png_end; twi_png++) {
        // insert the data into the allocated memory
        twi_png_bytes[i++] = *twi_png;
    }

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
    // create RWops from the image bytes
    wops = SDL_RWFromMem(twi_png_bytes, twi_img_size);
    // load image from RWops
    img = IMG_Load_RW(wops, 1);
    if(img == NULL)
        exit_msg("Couldn't load twi.png");

    // create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // create a texture from the image
    img_texture = SDL_CreateTextureFromSurface(renderer, img);

    // setup image rectangle so that we can control it
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = img->w;
    img_rect.h = img->h;

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

        // clear renderer
        SDL_RenderClear(renderer);
        // copy image into renderer to be rendered
        SDL_RenderCopy(renderer, img_texture, NULL, &img_rect);
        // render image
        SDL_RenderPresent(renderer);
    }

    return 0;
}
