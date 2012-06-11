#Minimum version of CMake to build this project
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Declaration et nommage du projet
PROJECT(prpa)

FIND_PACKAGE(OpenCV REQUIRED)

SET(CXX "g++")
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -W -Werror -pedantic -g")
SET(CMAKE_CXX_FLAGS "-Wall -W -Werror -pedantic")

#Defines subdirectory
ADD_SUBDIRECTORY(src/)
