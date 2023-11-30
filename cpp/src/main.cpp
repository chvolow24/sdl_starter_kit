#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "window.hpp"
#include "text.hpp"

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

    Window main_win(500, 500, "Test window");
    TextWriter open_sans_writer("assets/OpenSans-Regular.ttf", &main_win);
    main_win.set_TextWriter(&open_sans_writer);
    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    main_win.resize();
                }
            }
        }
        main_win.draw();
        SDL_Delay(1);
    }

}
