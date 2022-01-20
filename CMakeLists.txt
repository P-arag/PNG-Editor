cmake_minimum_required(VERSION 3.5)
project(PNG-Viewer
        VERSION 0.0.1
        DESCRIPTION "View png images in a powerful hex editor"
        LANGUAGES C)

add_executable(PNG-Viewer main.c)
target_include_directories(PNG-Viewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
