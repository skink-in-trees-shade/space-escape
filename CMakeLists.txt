cmake_minimum_required(VERSION 3.14)
project(space-escape)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(sdl2)
include(box2d)
include(entityx)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS source/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -O0 -g -pipe)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static box2d entityx)
target_include_directories(${PROJECT_NAME} PRIVATE source)