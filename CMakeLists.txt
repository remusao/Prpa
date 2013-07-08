#Minimum version of CMake to build this project
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Declaration et nommage du projet
PROJECT(prpa)

FIND_PACKAGE(OpenCV REQUIRED)

SET(CXX "g++")
SET(CMAKE_CXX_COMPILER  "/usr/bin/g++")
SET(CMAKE_CXX_FLAGS_DEBUG "-Wunused-local-typedefs -I/usr/include/eigen3 -std=c++11 -DEIGEN_NO_DEBUG -Wall -W -pedantic -g")
SET(CMAKE_CXX_FLAGS "-Wunused-local-typedefs -I/usr/include/eigen3 -std=c++11 -DEIGEN_NO_DEBUG -Wall -W -pedantic -O3")

#Defines subdirectory
ADD_SUBDIRECTORY(src/)
