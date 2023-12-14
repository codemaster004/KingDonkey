cmake_minimum_required(VERSION 3.27)
project(KingDonkey)

set(CMAKE_CXX_STANDARD 20)

include_directories(./sdl/include)
link_directories(./sdl/lib)

find_package(SDL2)

add_executable(KingDonkey src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Config/GameConfig.h)

target_link_libraries(KingDonkey SDL2::SDL2)
