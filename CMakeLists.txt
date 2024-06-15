cmake_minimum_required(VERSION 3.27)
project(Hexagon)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

if(WIN32)
    message(STATUS "Configuring for Windows")
    add_definitions(-DPLATFORM_WINDOWS)
elseif(UNIX)
    message(STATUS "Configuring for Linux")
    add_definitions(-DPLATFORM_LINUX)
endif()


include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)


FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(fmt)

add_executable(Hexagon
        main.cpp
        main/game_manager.cpp main/game_manager.h
        main/window_wrapper.cpp main/window_wrapper.h
        entities/game_entities.cpp
        entities/playable_sides.cpp entities/playable_sides.h entities/player.h entities/ai.h
        main/util.h
        entities/board.cpp
        entities/board.h
        entities/tile.h
        main/util.cpp
        main/background.cpp
        main/background.h
        main/background.h
        main/background.cpp
)
target_link_libraries(Hexagon sfml-graphics fmt)
