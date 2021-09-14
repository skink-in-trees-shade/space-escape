include(FetchContent)

FetchContent_Declare(EntityX GIT_REPOSITORY https://github.com/alecthomas/entityx.git GIT_TAG 1.3.0)

set(ENTITYX_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(ENTITYX_BUILD_SHARED OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(EntityX)