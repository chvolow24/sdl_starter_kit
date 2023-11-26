#ifndef SDL_STARTER_TEXT_H
#define SDL_STARTER_TEXT_H

#include "window.h"
#include "SDL_ttf.h"

/* Open a font from a ttf file */
TTF_Font *open_font(const char* path, int size, Window *win);

/* Write text to a destination rect. Target rect may be resized to fit text */
void write_text(const char *text, Window *win, SDL_Rect *dst_rect, TTF_Font *font, SDL_Color *color, bool allow_resize);


#endif