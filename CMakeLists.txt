cmake_minimum_required(VERSION 3.10)
project(SimpleNesEmulator C)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)
include_directories(include)
add_executable(SimpleNesEmulator ${SOURCES})
