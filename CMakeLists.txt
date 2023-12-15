cmake_minimum_required(VERSION 3.27)
project(KingDonkey)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_DIR ./sdl)
find_package(SDL2)

include_directories(sdl/include)
link_directories(sdl/lib)


add_executable(KingDonkey src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Config/GameConfig.h
        src/View/TextureManager.cpp
        src/View/TextureManager.h
        src/Model/GameObject.cpp
        src/Model/GameObject.h
        src/View/GameView.cpp
        src/View/GameView.h)

target_link_libraries(KingDonkey SDL2::SDL2)

add_custom_command(TARGET KingDonkey POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets
)