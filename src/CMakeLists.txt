cmake_minimum_required(VERSION 3.2)
project(gx2gl C)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_library(gx2gl gx2gl.c gx2glu.c gx2glut.c proc.c glff_shader.h context.h matrix.h matrix.c)
target_include_directories(gx2gl PRIVATE "${CMAKE_SOURCE_DIR}/include")
