cmake_minimum_required(VERSION 3.5)
project(PNG-Viewer
        VERSION 0.0.1
        DESCRIPTION "View png images in a powerful hex editor"
        LANGUAGES C)

file(GLOB_RECURSE SRC_FILES src/*.c)
add_executable(PNG-Viewer main.c ${SRC_FILES})
target_include_directories(PNG-Viewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
