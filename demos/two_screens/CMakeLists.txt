cmake_minimum_required(VERSION 3.2)
project(two_screens CXX)
include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

add_executable(two_screens main.cpp)

wut_enable_stdcpp(two_screens)

target_link_libraries(two_screens
   m
   whb
   gfd
   gx2
   proc_ui
   nsysnet
   sysapp
   gx2gl)

target_include_directories(two_screens PRIVATE "${WUT_ROOT}/include" "${CMAKE_SOURCE_DIR}/include")

wut_create_rpx(two_screens.rpx two_screens)
