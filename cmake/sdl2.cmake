include(FetchContent)

FetchContent_Declare(SDL2 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.0.16)

set(SDL_SHARED OFF)
set(SDL_ATOMIC OFF)
set(SDL_AUDIO OFF)
set(SDL_POWER OFF)
set(SDL_THREADS OFF)
set(SDL_TIMERS OFF)
set(SDL_CPUINFO OFF)
set(SDL_FILESYSTEM OFF)
set(SDL_SENSOR OFF)
set(SDL_LOCALE OFF)

FetchContent_MakeAvailable(SDL2)