
#include "SDL.h"
#include "window.h"

void draw_main(Window *win)
{
    SDL_SetRenderDrawColor(win->rend, 255, 0, 0, 255);
    int crosshair_r = 20;
    int x_Mid = win->w / 2;
    int y_Mid = win->h / 2;
    SDL_RenderDrawLine(win->rend, x_Mid - crosshair_r, y_Mid, x_Mid + crosshair_r, y_Mid);
    SDL_RenderDrawLine(win->rend, x_Mid, y_Mid + crosshair_r, x_Mid, y_Mid - crosshair_r);

}