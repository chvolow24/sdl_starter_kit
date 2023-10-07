#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"

#define DEFAULT_WINDOW_FLAGS SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE
#define DEFAULT_RENDER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC


void init_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nError initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }
}

int get_dpi_scale_factor(SDL_Window *win, SDL_Renderer *rend)
{
    int scale_factor = 0;
    int rw = 0, rh = 0, ww = 0, wh = 0;
    SDL_GetWindowSize(win, &ww, &wh);
    SDL_GetRendererOutputSize(rend, &rw, &rh);
    scale_factor = (float)rw / (float)ww;
    return scale_factor;
}


int main()
{
    init_SDL();

    SDL_Window *win = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, (Uint32)DEFAULT_WINDOW_FLAGS);
    if (!win) {
        fprintf(stderr, "Error creating window: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, (Uint32)DEFAULT_RENDER_FLAGS);
    if (!rend) {
        fprintf(stderr, "Error creating renderer: %s", SDL_GetError());
    }

    int scale_factor = get_dpi_scale_factor(win, rend);
    if (scale_factor == 0) {
        fprintf(stderr, "Error setting scale factor: %s", SDL_GetError());
    }
    printf("DPI scale factor: %d\n", scale_factor);

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
        SDL_Delay(1);
    }

}
