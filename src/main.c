#include <stdio.h>
#include "gengine.h"

int main(int argc, char *argv[]) {
    const char PATH[] = "/Users/hborcher/ClionProjects/playground/graphics/cmake-build-debug/scripts";
    const char CPATH[] = "/Users/hborcher/ClionProjects/playground/graphics/cmake-build-debug/lib";
    if(argc != 2){
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    lua_script *myscript = NULL;
    myscript = lua_script_create(argv[1], PATH, CPATH);
    lua_script_run(myscript);
    lua_script_destroy(&myscript);

    return 0;
}