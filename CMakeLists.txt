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
        src/View/GameView.h
        src/Utilities/Utility.cpp
        src/Utilities/Utility.h
        src/Model/EntityManager/Entity.h
        src/Utilities/DataStore.h
        src/Utilities/DataStore.tpp
        src/Model/Components/Component.h
        src/Utilities/BitDict.cpp
        src/Utilities/BitDict.h
        src/Model/Components/PositionComponent.cpp
        src/Model/Components/PositionComponent.h
        src/Model/PlayerModel.cpp
        src/Model/PlayerModel.h
        src/Model/EntityManager/Manager.h
        src/Model/EntityManager/Manager.cpp
        src/Model/Components/TextureComponent.cpp
        src/Model/Components/TextureComponent.h
)

target_link_libraries(KingDonkey SDL2::SDL2)

add_custom_command(TARGET KingDonkey POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets
)