cmake_minimum_required(VERSION 3.5)

project(ppm-io)

add_library(ppm-io INTERFACE)
target_compile_features(ppm-io INTERFACE)
target_include_directories(ppm-io INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)


