cmake_minimum_required(VERSION 3.2)
set(CMAKE_TOOLCHAIN_FILE $ENV{DEVKITPRO}/wut/share/wut.toolchain.cmake)
project(gx2gl)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)


add_subdirectory(src)
add_subdirectory(demos/nehe/lesson2)
add_subdirectory(demos/nehe/lesson6)
add_subdirectory(demos/two_screens)
