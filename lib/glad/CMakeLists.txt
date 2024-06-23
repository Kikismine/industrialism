cmake_minimum_required(VERSION 3.5)
project(glad C CXX)

add_library(glad)
target_sources(glad PRIVATE src/gl.c)
target_include_directories(glad PUBLIC include)