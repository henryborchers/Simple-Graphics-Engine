//
// Created by Borchers, Henry Samuel on 1/21/17.
//

#include <stdlib.h>
#include "window.h"


Window *window_create() {
    Window *temp = NULL;
    temp = (Window *) malloc(sizeof(Window));
    if (temp) {
        window_init(temp);
    }
    return temp;
}

int window_init(Window *temp) {
    if (temp == NULL) {
        return -1;
    }
    temp->background.r = 0;
    temp->background.g = 0;
    temp->background.b = 0;
    temp->background.a = 0;
    temp->height = -1;
    temp->width = -1;
    return 0;
}

void window_destroy(Window **pWindow) {
    Window *tmp = (*pWindow);
    tmp->height = -1;
    tmp->width = -1;
    SDL_DestroyRenderer(tmp->renderer);
    SDL_DestroyTexture(tmp->texture);
    SDL_DestroyWindow(tmp->window);
    free(tmp);
    *pWindow = NULL;
}

int window_open(Window *w) {
    int ret = 0;

    if ((ret = SDL_CreateWindowAndRenderer(w->width, w->height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN, &w->window,
                                           &w->renderer)) != 0) {
        fprintf(stderr, "Unable to create renderer and/or window\n");
        return ret;
    }
    SDL_SetWindowTitle(w->window, w->title);
    w->texture = SDL_CreateTexture(w->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w->width,
                                   w->height);
    if (NULL == w->texture) {
        fprintf(stderr, "Unable to create texture\n");
        ret = -1;
    }
    return ret;
}

int window_refresh(Window *w) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
//            puts("Quit");
            return 1;
        }
    }

    window_draw_background(w);
    return 0;
}

void window_draw_background(const Window *w) {
    SDL_SetRenderTarget(w->renderer, NULL);
    SDL_SetRenderDrawColor(w->renderer, w->background.r, w->background.g, w->background.b, w->background.a);
    SDL_RenderClear(w->renderer);
    SDL_RenderPresent(w->renderer);
}
