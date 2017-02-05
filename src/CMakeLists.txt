set(SOURCE_FILES main.c)
include_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(myprogram ${SOURCE_FILES})
target_link_libraries(myprogram gengine)
