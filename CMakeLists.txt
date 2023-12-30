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
        src/Model/Components/Component.h
        src/Utilities/DataStructures/BitDict.cpp
        src/Utilities/DataStructures/BitDict.h
        src/Model/Components/PositionComponent.cpp
        src/Model/Components/PositionComponent.h
        src/Model/PlayerModel.cpp
        src/Model/PlayerModel.h
        src/Model/EntityManager/Manager.h
        src/Model/EntityManager/Manager.cpp
        src/Model/Components/TextureComponent.cpp
        src/Model/Components/TextureComponent.h
        src/Utilities/MathVector.cpp
        src/Utilities/MathVector.h
        src/Model/Components/CollisionComponent.cpp
        src/Model/Components/CollisionComponent.h
        src/ViewModel/CollisionViewModel.cpp
        src/ViewModel/CollisionViewModel.h
        src/Model/Components/AnimationComponent.cpp
        src/Model/Components/AnimationComponent.h
        src/Model/Components/PhysicsComponent.cpp
        src/Model/Components/PhysicsComponent.h
        src/ViewModel/PlayerViewModel.cpp
        src/ViewModel/PlayerViewModel.h
        src/Model/GameLevelModel.cpp
        src/Model/GameLevelModel.h
        src/Utilities/Shapes/Shape.cpp
        src/Utilities/Shapes/Shape.h
        src/Utilities/DataStructures/ListSet.h
)

target_link_libraries(KingDonkey SDL2::SDL2)

add_custom_command(TARGET KingDonkey POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets
)