//
// Created by Borchers, Henry Samuel on 1/20/17.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <lualib.h>
#include <lauxlib.h>
#include "scripting.h"


//int simple_lua(const char *script_path, const char *lua_file) {
//
//    lua_State *L;
//    int ret;
//    char my_lua_starting_script[1024];
//
//    if (!lua_file) {
//        fprintf(stderr, "No file given\n");
//        return 1;
//    }
//
//    L = luaL_newstate();
//
//    if (NULL == L) {
//        return -1;
//    }
//
//    luaL_openlibs(L);
//
//    if ((ret = set_luaPath(L, script_path) != 0)) {
//        return ret;
//    };
//
//    snprintf(my_lua_starting_script, sizeof(my_lua_starting_script), "%s/%s", script_path, lua_file);
//
//    if ((ret = luaL_dofile(L, my_lua_starting_script)) != 0) {
//        fprintf(stderr, "Lua Error: %s\n", lua_tostring(L, -1));
//        return ret;
//    }
//
//    lua_close(L);
//    return 0;
//}

int set_luaPath(lua_State *pState, const char *path) {

    const int BUFFER_SIZE = 1024;

    const char *existing_path;
    char new_path[BUFFER_SIZE];


    lua_getglobal(pState, "package");
    lua_getfield(pState, -1, "path");
    existing_path = lua_tostring(pState, -1);

    if (snprintf(new_path, BUFFER_SIZE, "%s?.lua;%s", path, existing_path) < 0) {
        return -1;
    };
    lua_pop(pState, 1);
    lua_pushstring(pState, new_path);
    lua_setfield(pState, -2, "path");
    lua_pop(pState, 1);
    return 0;
}

int set_luaCPath(struct lua_State *pState, const char *path) {
    const int BUFFER_SIZE = 1024;

    const char *existing_path;
    char new_path[BUFFER_SIZE];


    lua_getglobal(pState, "package");
    lua_getfield(pState, -1, "cpath");
    existing_path = lua_tostring(pState, -1);

    if (snprintf(new_path, BUFFER_SIZE, "%s/?.dylib;%s", path, existing_path) < 0) {
        return -1;
    };
    lua_pop(pState, 1);
    lua_pushstring(pState, new_path);
    lua_setfield(pState, -2, "cpath");
    lua_pop(pState, 1);
    return 0;
}

lua_script *lua_script_create(const char *filename, const char *lua_path, const char *cpath) {

    lua_script *tmp = NULL;
    size_t len;

    if (NULL == filename) {
        return NULL;
    }

    tmp = (lua_script *) malloc(sizeof(lua_script));
    if (NULL == tmp) {
        return tmp;
    } else {
        tmp->filename = NULL;
        tmp->lua_path = NULL;
        tmp->cpath = NULL;
        tmp->L = NULL;
    }

    // Load the load state
    tmp->L = luaL_newstate();
    if (NULL == tmp->L) {
        free(tmp);
        return NULL;
    } else {
        luaL_openlibs(tmp->L);
    }
    // filename
    len = strlen(filename);
    if (len) {
        tmp->filename = calloc(sizeof(char), len + 1);
        if (NULL != filename) {
            strncpy(tmp->filename, filename, len);

        } else {
            free(tmp);
            return NULL;
        }
    }

    // lua_path
    if (lua_path) {
        len = strlen(lua_path);
        if (len) {
            tmp->lua_path = calloc(sizeof(char), len + 1);
            if (NULL != lua_path) {
                strncpy(tmp->lua_path, lua_path, len);

            }
        }

    }

    // cpath
    if (cpath) {
        len = strlen(cpath);
        if (len) {
            tmp->cpath = calloc(sizeof(char), len + 1);
            if (NULL != cpath) {
                strncpy(tmp->cpath, cpath, len);

            }
        }

    }


    return tmp;
}

void lua_script_destroy(lua_script **pScript) {
    lua_script *tmp = *(pScript);
    lua_close(tmp->L);

    free(tmp->filename);

    if (tmp->lua_path) {
        free(tmp->lua_path);
    }

    if (tmp->cpath) {
        free(tmp->cpath);
    }
    free(tmp);
    *(pScript) = NULL;

}

int lua_script_run(const lua_script *script) {
    const int MAX_SIZE = 1024;
    char start_script[MAX_SIZE];
    int ret;

    // Set the Lua module path
    if (script->lua_path) {
        if ((ret = set_luaPath(script->L, script->lua_path)) != 0) {
            return ret;
        };
    }

    // todo: the Lua module cpath
    if (script->cpath) {
        if ((ret = set_luaCPath(script->L, script->cpath)) != 0) {
            return ret;
        };
    }
    // get full path of the script
    if (script->lua_path) {
        snprintf(start_script, MAX_SIZE, "%s/%s", script->lua_path, script->filename);

    } else {
        strcpy(start_script, script->filename);
    }
    if ((ret = luaL_dofile(script->L, start_script)) != 0) {
        fprintf(stderr, "Lua Error: %s\n", lua_tostring(script->L, -1));
        return ret;
    }

    return 0;
}


