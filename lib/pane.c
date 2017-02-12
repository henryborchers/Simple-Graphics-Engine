//
// Created by Borchers, Henry Samuel on 2/11/17.
//

#include "pane.h"

Pane *pane_create(Window *parent, int width, int height) {
    Pane *new_pane = NULL;
    if (NULL == parent) {
        return NULL;
    }
    new_pane = (Pane *) malloc(sizeof(Pane));
    if (NULL == new_pane) {

        return NULL;
    } else {
        pane_init(new_pane);
        new_pane->size.height = height;
        new_pane->size.width = width;
        new_pane->texture = SDL_CreateTexture(parent->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                              width, height);

//      // initalize background color to white
        new_pane->background.r = 255;
        new_pane->background.g = 255;
        new_pane->background.b = 255;
        new_pane->background.a = 255;
        // Add new pane to parent
        if (parent->children.amount >= parent->children.container_size) {
            int newsize = parent->children.container_size * 2;
            parent->children.children = realloc(parent->children.children, sizeof(Pane *) * newsize);
            parent->children.container_size = newsize;
        }
        parent->children.children[parent->children.amount] = new_pane;
        parent->children.amount++;
        return new_pane;
    }
}

void pane_destroy(Pane **p) {
    if (NULL != (*p)) {
        SDL_DestroyTexture((*p)->texture);
        free(*(p));
        *p = NULL;
    }
}

int pane_init(Pane *p) {
    p->orientation.x = 0;
    p->orientation.y = 0;
    return 0;
}

int pane_refresh(const Pane *p, const Window *window) {
    SDL_Rect dst;
    int window_t_width;
    int window_t_height;

    if (NULL == p) {
        return -1;
    }
    SDL_SetRenderTarget(window->renderer, p->texture);
    SDL_QueryTexture(window->texture, NULL, NULL, &window_t_width, &window_t_height);
    dst.x = p->orientation.x;
    dst.y = p->orientation.y;

    float texture_ratio_width = (float) p->size.width / (float) window_t_width;
    float texture_ratio_height = (float) p->size.height / (float) window_t_height;
    float screen_ratio_width = (float) window->size.width / window_t_width;
    float screen_ratio_height = (float) window->size.height / window_t_height;
    int width = (int) (texture_ratio_width * window->size.width);
    int height = (int) (texture_ratio_height * window->size.height);


    dst.x = (int) (p->orientation.x * screen_ratio_width);
    dst.y = (int) (p->orientation.y * screen_ratio_height);
    dst.w = width;
    dst.h = height;
    SDL_SetRenderDrawColor(window->renderer,
                           p->background.r,
                           p->background.g,
                           p->background.b,
                           p->background.a);

    SDL_RenderClear(window->renderer);
    SDL_SetRenderTarget(window->renderer, NULL);
    SDL_RenderCopy(window->renderer, p->texture, NULL, &dst);
    return 0;
}


