cmake_minimum_required(VERSION 3.5)
project(PNG-Editor
        VERSION 0.0.1
        DESCRIPTION "View png images in a powerful hex editor"
        LANGUAGES C)
find_package(ZLIB)

file(GLOB_RECURSE SRC_FILES src/*.c)
add_executable(PNG-Editor main.c ${SRC_FILES})
target_link_libraries(PNG-Editor z)
target_include_directories(PNG-Editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
