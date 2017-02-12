//
// Created by Borchers, Henry Samuel on 1/21/17.
//

#include <stdlib.h>
#include "window.h"


Window *window_create() {
    Window *temp = NULL;
    temp = (Window *) malloc(sizeof(Window));
    if (temp) {
        temp->children.container_size = CHILDREN_CONTAINER_START_SIZE;
        temp->children.children = calloc(sizeof(void**), CHILDREN_CONTAINER_START_SIZE);
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
    temp->size.height = -1;
    temp->size.width = -1;
    temp->children.amount = 0;
    temp->children.container_size = CHILDREN_CONTAINER_START_SIZE;
    return 0;
}

void window_destroy(Window **pWindow) {
    Window *tmp = *(pWindow);
    tmp->size.height = -1;
    tmp->size.width = -1;
    SDL_DestroyRenderer(tmp->renderer);
    SDL_DestroyTexture(tmp->texture);
    SDL_DestroyWindow(tmp->window);
    for(int i = 0; i < tmp->children.amount; i++){
        Pane *p = (Pane*)tmp->children.children[i];
        if(p != NULL){
            pane_destroy(&p);
        }
    }
    free(tmp);
    *pWindow = NULL;
}

int window_open(Window *w) {
    int ret = 0;

    if ((ret = SDL_CreateWindowAndRenderer(w->size.width, w->size.height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN, &w->window,
                                           &w->renderer)) != 0) {
        fprintf(stderr, "Unable to create renderer and/or window\n");
        return ret;
    }
    SDL_SetWindowTitle(w->window, w->title);
    w->texture = SDL_CreateTexture(w->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w->size.width,
                                   w->size.height);
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
            return 1;
        }
    }
    SDL_GetWindowSize(w->window, &w->size.width, &w->size.height);
    window_draw_background(w);
    for(int i = 0; i < w->children.amount; i++){
        Pane* child = w->children.children[i];
        if(NULL != child){
            pane_refresh(child, w);
        }
    }
    SDL_RenderPresent(w->renderer);
    return 0;
}

void window_draw_background(const Window *w) {
    SDL_SetRenderTarget(w->renderer, NULL);
    SDL_SetRenderDrawColor(w->renderer, w->background.r, w->background.g, w->background.b, w->background.a);
    SDL_RenderClear(w->renderer);

}
