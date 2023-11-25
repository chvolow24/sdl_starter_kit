#ifndef SDL_STARTER_WINDOW_H
#define SDL_STARTER_WINDOW_H

#include "SDL.h"

typedef struct window {
    SDL_Window *win;
    SDL_Renderer *rend;
    double dpi_scale_factor;
    int w;
    int h;
} Window;

/* Create a new Window struct and initialize all members */
Window *create_window(int w, int h, const char *name);

/* Reset the values of the w and h members of a Window struct based on current window dimensions */
void resize_window(Window *window);

#endif

