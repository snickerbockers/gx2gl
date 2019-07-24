cmake_minimum_required(VERSION 3.2)
set(CMAKE_TOOLCHAIN_FILE $ENV{WUT_ROOT}/share/wut.toolchain.cmake)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_subdirectory(src)
add_subdirectory(demos/nehe/lesson2)
