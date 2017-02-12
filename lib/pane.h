//
// Created by Borchers, Henry Samuel on 2/11/17.
//

#ifndef GRAPHICS_PANE_H
#define GRAPHICS_PANE_H


#include "gengine.h"

Pane *pane_create(Window *parent, int width, int height);

int pane_init(Pane *p);

int pane_refresh(const Pane *p, const Window *window);

void pane_destroy(Pane **p);

#endif //GRAPHICS_PANE_H
