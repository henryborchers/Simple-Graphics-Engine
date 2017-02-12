//
// Created by Borchers, Henry Samuel on 2/4/17.
//

#include "lua_glue.h"
#include "gengine.h"

const char *NS_WINDOW = "Graphics_Window";
const char *NS_PANE = "Graphics_PANE";

typedef struct {
    Window *window;
    char *name;
} lwindow;

typedef struct {
    Pane *pane;
} lpane;

// PROTOTYPES
// WINDOW
static void graphics_create_metatable(lua_State *l, const luaL_Reg *reg, const char *name);

static int window_Lnew(lua_State *l);

static int window_Lmainloop(lua_State *l);

static int window_LsetColor(lua_State *l);

static int window_tostring(lua_State *l);

static int window_gc(lua_State *l);

static int window_LCreatePane(lua_State *l);

// Pane
static int pane_tostring(lua_State *l);

//static int pane_gc(lua_State *l);

static int pane_setOrientation(lua_State *l);

static int pane_setSize(lua_State *l);

static int pane_LsetColor(lua_State *l);

// WINDOW
// WINDOW Functions
static const luaL_Reg window_funcs[] = {
        {"new", window_Lnew},
        {NULL, NULL}
};

static const luaL_Reg window_methods[] = {
        {"__tostring", window_tostring},
        {"__gc",       window_gc},
        {"mainloop",   window_Lmainloop},
        {"createPane", window_LCreatePane},
        {"setColor",   window_LsetColor},
        {NULL, NULL}
};

static const luaL_Reg pane_methods[] = {
        {"__tostring",     pane_tostring},
        {"setColor",       pane_LsetColor},
        {"setSize",        pane_setSize},
        {"setOrientation", pane_setOrientation},
        {NULL, NULL}
};


int window_Lnew(lua_State *l) {
    lwindow *w = NULL;
    int height;
    int width;
    const char *name;

    width = luaL_checkint(l, 1);
    height = luaL_checkint(l, 2);
    name = luaL_checkstring(l, 3);
    luaL_argcheck(l, width > 0, 1, "Invalid width");
    luaL_argcheck(l, height > 0, 2, "Invalid height");
    lua_newtable(l);
    w = lua_newuserdata(l, sizeof(lwindow));

    if (NULL == w) {
        fprintf(stderr, "unable to allocate");
        return 0;
    }
    luaL_setmetatable(l, NS_WINDOW);

    w->window = window_create();
    if (NULL == w->window) {
        fprintf(stderr, "unable to allocate window");

        return 0;
    }
    w->window->size.width = width;
    w->window->size.height = height;
    w->window->title = strdup(name); // FIXME!
    w->name = strdup(name); // FIXME!
    window_open(w->window);
    return 1;
}

int window_tostring(lua_State *l) {
    lwindow *w = NULL;
    w = (lwindow *) lua_touserdata(l, 1);

    lua_pushfstring(l, "I'm %d by %d.\n", w->window->size.width, w->window->size.height);
    return 1;
}

int window_gc(lua_State *l) {
    lwindow *w = NULL;
    w = (lwindow *) lua_touserdata(l, 1);
    window_destroy(&w->window);
    return 0;
}

int window_Lmainloop(lua_State *l) {
    int ret;

    lwindow *w = NULL;
    w = (lwindow *) lua_touserdata(l, 1);
    if (NULL == w) {
        fprintf(stderr, "main loop failed!\n");
        return 0;
    }
    ret = window_refresh(w->window);

    switch (ret) {
        case 0:
            lua_pushboolean(l, 1);
            break;
        case 1:
            lua_pushboolean(l, 0);
            break;
        default:
            return 0;
    }

    return 1;
}

int window_LsetColor(lua_State *l) {
    lwindow *w = NULL;
    w = (lwindow *) lua_touserdata(l, 1);
    int red;
    int green;
    int blue;
    int alpha;

    red = luaL_checkint(l, 2);
    green = luaL_checkint(l, 3);
    blue = luaL_checkint(l, 4);
    alpha = luaL_checkint(l, 5);

    luaL_argcheck(l, 0 <= red && red <= 255, 2, "red value is not within the valid range");
    luaL_argcheck(l, 0 <= green && green <= 255, 3, "green value is not within the valid range");
    luaL_argcheck(l, 0 <= blue && blue <= 255, 4, "blue value is not within the valid range");
    luaL_argcheck(l, 0 <= alpha && alpha <= 255, 5, "alpha value is not within the valid range");

    w->window->background.r = (uint8_t) red;
    w->window->background.g = (uint8_t) green;
    w->window->background.b = (uint8_t) blue;
    w->window->background.a = (uint8_t) alpha;

    return 0;
}

int window_LCreatePane(lua_State *l) {
    lpane *p = NULL;
    lwindow *w = NULL;
    w = luaL_checkudata(l, 1, NS_WINDOW);
    int width = luaL_checkint(l, 2);
    int height = luaL_checkint(l, 3);
    if (NULL == w) {
        puts("Unable to load userdata");
        return 0;
    }
    p = lua_newuserdata(l, sizeof(lpane));
    if (NULL == p) {
        fprintf(stderr, "Unable to allocate a new pane");
        return 0;
    }
    luaL_setmetatable(l, NS_PANE);
    p->pane = pane_create(w->window, width, height);
    if (NULL == p->pane) {
        fprintf(stderr, "Unable to create a panel");
        return 0;
    }
    return 1;
}

// Pane Functions
int pane_tostring(lua_State *l) {
    lpane *w = NULL;
    puts("Calling "__FILE__);
    w = (lpane *) lua_touserdata(l, 1);

    lua_pushfstring(l, "I'm a pane %d by %d.\n", w->pane->size.width, w->pane->size.height);
    return 1;
}


//int pane_gc(lua_State *l) {
//    lpane *p = NULL;
//    p = (lpane *) lua_touserdata(l, 1);
//    pane_destroy(&p->pane);
//    return 0;
//}


int pane_setOrientation(lua_State *l) {
    lpane *p = luaL_checkudata(l, 1, NS_PANE);
    int x = luaL_checkint(l, 2);
    int y = luaL_checkint(l, 3);
    if (NULL != p) {
        p->pane->orientation.x = x;
        p->pane->orientation.y = y;
    }
    return 0;
}

int pane_setSize(lua_State *l) {
    lpane *p = luaL_checkudata(l, 1, NS_PANE);
    int width = luaL_checkint(l, 2);
    int height = luaL_checkint(l, 3);
    if (NULL != p) {
        p->pane->size.width = width;
        p->pane->size.height = height;
    }
    return 0;

}

int pane_LsetColor(lua_State *l) {
    lpane *p = NULL;
    p = (lpane *) luaL_checkudata(l, 1, NS_PANE);
    int red;
    int green;
    int blue;
    int alpha;

    red = luaL_checkint(l, 2);
    green = luaL_checkint(l, 3);
    blue = luaL_checkint(l, 4);
    alpha = luaL_checkint(l, 5);

    luaL_argcheck(l, 0 <= red && red <= 255, 2, "red value is not within the valid range");
    luaL_argcheck(l, 0 <= green && green <= 255, 3, "green value is not within the valid range");
    luaL_argcheck(l, 0 <= blue && blue <= 255, 4, "blue value is not within the valid range");
    luaL_argcheck(l, 0 <= alpha && alpha <= 255, 5, "alpha value is not within the valid range");

    p->pane->background.r = (uint8_t) red;
    p->pane->background.g = (uint8_t) green;
    p->pane->background.b = (uint8_t) blue;
    p->pane->background.a = (uint8_t) alpha;
    return 0;
}

/////////////////////
// Utility functions
/////////////////////
void graphics_create_metatable(lua_State *l, const luaL_Reg *reg, const char *name) {
    luaL_newmetatable(l, name);
    lua_pushvalue(l, -1);
    lua_setfield(l, -1, "__index");
    luaL_setfuncs(l, reg, 0);
    lua_pop(l, 1);
}



////////////////////////////////
// Register functions with Lua
////////////////////////////////

int luaopen_libgengine(lua_State *l) {
    if (graphics_init() != 0) {
        return 0;
    }
    graphics_create_metatable(l, window_methods, NS_WINDOW);
    lua_newtable(l);
    luaL_newlib(l, window_funcs);
    lua_setfield(l, -2, "window");
    graphics_create_metatable(l, pane_methods, NS_PANE);

    return 1;
}
