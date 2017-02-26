cmake_minimum_required(VERSION 3.6)
project(graphics)
set(CMAKE_C_STANDARD 99)

find_package(lua REQUIRED)
find_package(SDL2 REQUIRED)
set(scripts_src
        scripts
        scripts/fun.lua
        scripts/hypnotoad.lua
        scripts/repl.lua
        )
add_subdirectory(lib)
add_subdirectory(src)
add_custom_target(lua_scripts ALL
    DEPENDS ${scripts_src}

        )
add_custom_command(OUTPUT ${scripts_src}

        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/scripts ${CMAKE_BINARY_DIR}/scripts
        COMMENT "Copying scripts to build folder"
        )