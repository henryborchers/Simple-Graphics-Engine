//
// Created by Borchers, Henry Samuel on 1/21/17.
//

#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include "gengine.h"
#include "window.h"
#include <SDL2/SDL.h>

typedef struct {
    int height;
    int width;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Color background;
    char *title;
} Window;

Window *window_create();

int window_init(Window *temp);

int window_refresh(Window *w);

int window_open(Window *w);

void window_draw_background(const Window *w);

void window_destroy(Window **pWindow);

#endif //GRAPHICS_WINDOW_H
