#include <stdbool.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "window.h"


TTF_Font *open_font(const char* path, int size, Window *win)
{
    size *= win->dpi_scale_factor;
    TTF_Font *font = TTF_OpenFont(path, size);
    if (!font) {
        fprintf(stderr, "\nError: failed to open font: %s", TTF_GetError());
        exit(1);
    }
    return font;
}


void write_text(const char *text, Window *win, SDL_Rect *dst_rect, TTF_Font *font, SDL_Color *color, bool allow_resize)
{
    if (strlen(text) == 0) {
        return;
    }

    SDL_Rect new_rect = {dst_rect->x, dst_rect->y, 0, 0};
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = TTF_RenderUTF8_Blended(font, text, *color);
    if (!surface) {
        fprintf(stderr, "\nError: TTF_RenderText_Blended failed: %s", TTF_GetError());
        return;
    }
    texture = SDL_CreateTextureFromSurface(win->rend, surface);

    SDL_QueryTexture(texture, NULL, NULL, &(new_rect.w), &(new_rect.h));
    if (!texture) {
        fprintf(stderr, "\nError: SDL_CreateTextureFromSurface failed: %s", TTF_GetError());
        return;
    }

    if (allow_resize) {
        dst_rect->w = new_rect.w;
        dst_rect->h = new_rect.h;
    }

    SDL_RenderCopy(win->rend, texture, NULL, &new_rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}