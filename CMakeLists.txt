cmake_minimum_required(VERSION 3.27)
project(KingDonkey)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2)

add_executable(KingDonkey src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Config/GameConfig.h
        src/View/TextureManager.cpp
        src/View/TextureManager.h
        src/View/GameView.cpp
        src/View/GameView.h
        src/Utilities/Utility.cpp
        src/Utilities/Utility.h
        src/Model/EntityManager/Entity.h
        src/Utilities/DataStructures/DataStore.h
        src/Utilities/DataStructures/DataStore.tpp
        src/Model/Components/EntityComponent.h
        src/Utilities/DataStructures/BitDict.cpp
        src/Utilities/DataStructures/BitDict.h
        src/Model/Components/Position.cpp
        src/Model/Components/Position.h
        src/Model/PlayerModel.h
        src/Model/EntityManager/Manager.h
        src/Model/EntityManager/Manager.cpp
        src/Model/Components/Texture.cpp
        src/Model/Components/Texture.h
        src/Utilities/MathVector.cpp
        src/Utilities/MathVector.h
        src/Model/Components/Collision.cpp
        src/Model/Components/Collision.h
        src/ViewModel/CollisionViewModel.cpp
        src/ViewModel/CollisionViewModel.h
        src/Model/Components/Animation.cpp
        src/Model/Components/Animation.h
        src/Model/Components/Physics.cpp
        src/Model/Components/Physics.h
        src/ViewModel/PlayerViewModel.cpp
        src/ViewModel/PlayerViewModel.h
        src/Model/GameLevelModel.cpp
        src/Model/GameLevelModel.h
        src/Utilities/Shapes/Shape.cpp
        src/Utilities/Shapes/Shape.h
        src/Utilities/DataStructures/ListSet.h
        src/Utilities/Timer.cpp
        src/Utilities/Timer.h
        src/Model/Components/Keyboard.cpp
        src/Model/Components/Keyboard.h
)

target_link_libraries(KingDonkey SDL2::SDL2)

add_custom_command(TARGET KingDonkey POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets
)