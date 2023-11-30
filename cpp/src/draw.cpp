#include "text.hpp"

void Window::draw()
{
    /* Draw background */
    set_rend_draw_color(0, 0, 0, 255);
    render_clear();

    /* Write some text */
    SDL_Color white = (SDL_Color) {255, 255, 255, 255};
    text_writer->set_size(28);
    text_writer->set_color(white);
    SDL_Rect dst1 = {25, 25, 0, 0};
    text_writer->write("Hello", &dst1);


    render_present();

}