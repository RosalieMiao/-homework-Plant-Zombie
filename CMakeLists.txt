cmake_minimum_required(VERSION 3.12)
project(Plants_Zombies)

set(CMAKE_CXX_STANDARD 14)

add_executable(Plants_Zombies main.cpp zombie.cpp zombie.h plant.cpp plant.h game.cpp game.h bullet.cpp bullet.h object.cpp object.h)