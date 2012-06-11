#Minimum version of CMake to build this project
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Declaration et nommage du projet
PROJECT(prpa)

FIND_PACKAGE(OpenCV REQUIRED)

SET(CXX "clang++")
SET(CMAKE_CXX_COMPILER  "/usr/bin/clang++")
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -W -Werror -pedantic -g")
SET(CMAKE_CXX_FLAGS "-Wall -W -Werror -pedantic -O3")

#Defines subdirectory
ADD_SUBDIRECTORY(src/)
