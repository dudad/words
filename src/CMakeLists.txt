cmake_minimum_required(VERSION 3.10)

# set the project name
project(words)

set(CMAKE_BUILD_TYPE Debug)

# add the executable
add_executable(words main.cpp Application.cpp Config.cpp CurrModeHandler.cpp EventHandler.cpp Input.cpp Mode.cpp Params.cpp TimeStats.cpp WordProvider.cpp)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})
