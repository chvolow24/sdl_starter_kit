#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "window.hpp"

#define STD_FONT_SIZES {10, 12, 14, 16, 18, 24, 30, 36, 48, 60, 72}
#define STD_FONT_ARRLEN 11

class TextWriter {
    public:
        TextWriter(const char *font_filepath, Window *win) : win(win), font_path(font_filepath), color((SDL_Color) {0, 0, 0, 255}) {
            int std_font_sizes[] = STD_FONT_SIZES;
            for (int i=0; i<STD_FONT_ARRLEN; i++) {
                SDL_fonts[i] = TTF_OpenFont(font_filepath, std_font_sizes[i] * win->get_dpi_scale_factor());
            }
        }
        void set_color(SDL_Color set_color) {
            color = set_color;
        }
        void set_size(int font_size) {
            int std_font_sizes[] = STD_FONT_SIZES;
            active_font_index = 0;
            while (active_font_index < STD_FONT_ARRLEN && (std_font_sizes[active_font_index] < font_size)) {
                active_font_index++;
            }
        }
        void write(std::string text_to_write, SDL_Rect *dst_rect) {
            SDL_Rect new_rect = {dst_rect->x, dst_rect->y, 0, 0};
            SDL_Surface *surface;
            SDL_Texture *texture;
            surface = TTF_RenderUTF8_Blended(SDL_fonts[active_font_index], text_to_write.c_str(), color);
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

            SDL_RenderCopy(win->rend, texture, NULL, &new_rect);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
    private:
        Window *win;
        const char *font_path;
        TTF_Font *SDL_fonts[STD_FONT_ARRLEN];
        SDL_Color color;
        int active_font_index;
};