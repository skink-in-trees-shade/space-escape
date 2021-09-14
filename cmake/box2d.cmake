include(FetchContent)

FetchContent_Declare(Box2D GIT_REPOSITORY https://github.com/erincatto/box2d.git GIT_TAG v2.4.1)

set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(Box2D)