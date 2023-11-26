#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "draw.h"
#include "window.h"
#include "text.h"

void init_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nError initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }
}

void init_SDL_ttf()
{
    if (TTF_Init() != 0) {
        fprintf(stderr, "\nError: TTF_Init failed: %s", TTF_GetError());
        exit(1);
    }
}


int main()
{
    init_SDL();
    init_SDL_ttf();

    Window *main_win = create_window(1200, 900, "Hello there");

    TTF_Font *open_sans = open_font("assets/OpenSans-Regular.ttf", 14, main_win);

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    resize_window(main_win);
                    printf("New window size: %d, %d\n", main_win->w, main_win->h);
                }
            }
        }
        SDL_SetRenderDrawColor(main_win->rend, 0, 0, 0, 0);
        SDL_RenderClear(main_win->rend);
        draw_main(main_win);
        SDL_RenderPresent(main_win->rend);
        SDL_Delay(1);
    }

}
