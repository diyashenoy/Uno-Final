cmake_minimum_required(VERSION 3.14)
project(Uno)

set(CMAKE_CXX_STANDARD 14)

add_executable(Uno Move.cpp Move.h Card.cpp Card.h Game.cpp Game.h Player.cpp Player.h main.cpp)