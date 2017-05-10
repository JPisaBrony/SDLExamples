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
SDL_Rect img_rect;

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

    // create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // create a texture from the image
    img_texture = SDL_CreateTextureFromSurface(renderer, img);

    // setup image rectangle so that we can control it
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = img->w;
    img_rect.h = img->h;

    // clear renderer
    SDL_RenderClear(renderer);
    // copy image into renderer to be rendered
    SDL_RenderCopy(renderer, img_texture, NULL, &img_rect);
    // render image
    SDL_RenderPresent(renderer);

    // wait 3 seconds
    SDL_Delay(3000);

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

    return 0;
}
