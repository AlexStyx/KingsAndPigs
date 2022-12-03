cmake_minimum_required(VERSION 3.14)
project(KingsAndPigs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp tinyxml2.cpp tinyxml2.h Game.cpp Game.h Parser.cpp Parser.h)
add_executable(KingsAndPigs ${SOURCE_FILES} Level.cpp Level.h InputHandler.cpp InputHandler.h Player.h Map.h Animation.cpp Animation.h)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(KingsAndPigs sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_library(tinyxml2 ${SOURCE_FILES})