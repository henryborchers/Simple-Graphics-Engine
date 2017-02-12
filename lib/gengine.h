//
// Created by Borchers, Henry Samuel on 1/20/17.
//

#ifndef GRAPHICS_GENGINE_H
#define GRAPHICS_GENGINE_H

#include <SDL2/SDL.h>


typedef struct {
    int x;
    int y;
} Orientation;

typedef struct {
    int width;
    int height;
} Size;


typedef struct {
    int amount;
    int container_size;
    void **children;
} Children;


typedef struct {
    Size size;
    Orientation orientation;
    SDL_Texture *texture;
    SDL_Color background;
} Pane;


typedef struct {
    Children children;
    Size size;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Color background;
    char *title;

} Window;


#include "graphics.h"
#include "scripting.h"
#include "pane.h"
#include "window.h"


#endif //GRAPHICS_GENGINE_H
