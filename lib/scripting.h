//
// Created by Borchers, Henry Samuel on 1/20/17.
//

#ifndef GRAPHICS_SCRIPTING_H
#define GRAPHICS_SCRIPTING_H

#include <lua.h>

typedef struct {
    char *filename;
    char *lua_path;
    char *cpath;
    lua_State *L;
} lua_script;

lua_script *lua_script_create(const char *filename, const char *lua_path, const char *cpath);

int lua_script_run(const lua_script *script);

void lua_script_destroy(lua_script **pScript);

//int simple_lua(const char *script_path, const char *lua_file);

int set_luaPath(struct lua_State *pState, const char *path);

int set_luaCPath(struct lua_State *pState, const char *path);


#endif //GRAPHICS_SCRIPTING_H
