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

add_executable(Hexagon main.cpp game.cpp
        game.h
        window_wrapper.cpp
        window_wrapper.h
        game_entities.cpp
        game_entities.h
)
target_link_libraries(Hexagon sfml-graphics fmt)
