#pragma once

#include <iostream>
#include <string>
#include "SDL.h"

#define DEFAULT_WINDOW_FLAGS SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE
#define DEFAULT_RENDER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC


class TextWriter;

class Window {
    public:
        int w;
        int h;
        SDL_Renderer *rend;
        Window(int w_set, int h_set, std::string name) 
        {
            win = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_set, h_set, (Uint32)DEFAULT_WINDOW_FLAGS);
            if (!win) {
                fprintf(stderr, "Error creating window: %s", SDL_GetError());
                exit(1);
            }

            rend = SDL_CreateRenderer(win, -1, (Uint32)DEFAULT_RENDER_FLAGS);
            if (!rend) {
                fprintf(stderr, "Error creating renderer: %s", SDL_GetError());
            }

            dpi_scale_factor = 0;
            int rw = 0, rh = 0, ww = 0, wh = 0;
            SDL_GetWindowSize(win, &ww, &wh);
            SDL_GetRendererOutputSize(rend, &rw, &rh);

            dpi_scale_factor = (double) rw / ww;
            
            if (dpi_scale_factor == 0 || dpi_scale_factor != (double) rh / wh) {
                fprintf(stderr, "Error setting scale factor: %s", SDL_GetError());
                exit(1);
            }
            w = w_set * dpi_scale_factor;
            h = h_set * dpi_scale_factor;
        }
        double get_dpi_scale_factor()
        {
            return dpi_scale_factor;
        }
        void set_TextWriter(TextWriter *tw) {
            text_writer = tw;
        }
        void resize()
        {
            SDL_GetWindowSize(win, &w, &h);
        }
        void set_rend_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            SDL_SetRenderDrawColor(rend, r, g, b, a);
            color_r = r;
            color_g = g;
            color_b = b;
            color_a = a;
        }
        void render_clear()
        {
            SDL_RenderClear(rend);
        }
        void render_present()
        {
            SDL_RenderPresent(rend);
        }
        void print_addresses()
        {
            std::cout << "Win: " << win << "; Rend: " << rend << std::endl;
        }
        void print_dims()
        {
            std::cout << "Window dims: (" << w << "," << h <<")\n";
        }
        void draw_line(int x1, int y1, int x2, int y2);
        void draw();

    private:
        SDL_Window *win;
        double dpi_scale_factor;
        uint8_t color_r;
        uint8_t color_g;
        uint8_t color_b;
        uint8_t color_a;
        TextWriter *text_writer;
};