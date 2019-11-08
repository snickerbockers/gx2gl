cmake_minimum_required(VERSION 3.2)
project(lesson06 C)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(lesson06 lesson6.c)

wut_enable_stdcpp(lesson06)

target_link_libraries(lesson06
   whb
   gfd
   gx2
   proc_ui
   nsysnet
   sysapp
   gx2gl
   m)

target_include_directories(lesson06 PRIVATE "${WUT_ROOT}/include" "${CMAKE_SOURCE_DIR}/include")

wut_create_rpx(lesson06.rpx lesson06)
