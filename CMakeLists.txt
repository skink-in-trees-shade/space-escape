cmake_minimum_required(VERSION 3.15)
project(space-escape CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(entityx REQUIRED)
find_package(box2d REQUIRED)
find_package(fruit REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer entityx::entityx box2d::box2d fruit::fruit)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/source)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/package)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_SOURCE_DIR}/package)