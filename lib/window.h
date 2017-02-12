//
// Created by Borchers, Henry Samuel on 1/21/17.
//

#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

static const int CHILDREN_CONTAINER_START_SIZE = 8;

#include <SDL2/SDL.h>
#include "gengine.h"



Window *window_create();

int window_init(Window *temp);

int window_refresh(Window *w);

int window_open(Window *w);

void window_draw_background(const Window *w);

void window_destroy(Window **pWindow);

#endif //GRAPHICS_WINDOW_H
