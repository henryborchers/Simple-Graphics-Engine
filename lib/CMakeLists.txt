set(SOURCE_FILES
        gengine.c gengine.h
        graphics.c graphics.h
        scripting.h scripting.c
        window.c window.h
        pane.c pane.h
        lua_glue.c lua_glue.h
        )
set(DEPENDENCIES_FOUND yes)

if (NOT LUA_FOUND)
    set(DEPENDENCIES_FOUND no)
    message(WARNING "Lua not found")
endif ()

if (NOT SDL2_FOUND)
    set(DEPENDENCIES_FOUND no)
    message(WARNING "SDL not found")
endif ()


if (NOT DEPENDENCIES_FOUND)
    message(WARNING "DEPENDENCIES NOT FOUND")
ELSE ()
    message(STATUS "FOUND DEPENDENCIES")
    add_library(gengine SHARED ${SOURCE_FILES})

    target_include_directories(gengine PRIVATE ${LUA_INCLUDE_DIR})
    target_link_libraries(gengine ${LUA_LIBRARIES})

    target_include_directories(gengine PRIVATE ${SDL2_INCLUDE_DIR})
    target_link_libraries(gengine ${SDL2_LIBRARIES})
endif ()
