include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(filter)

file(GLOB HH_FILES *.hh)
file(GLOB SRC_FILES *.cc)
file(GLOB HXX_FILES *.hxx)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}  "${CMAKE_CURRENT_SOURCE_DIR}/../CMake/FindTBB/")

find_package(BISON)
find_package(FLEX)
FIND_PACKAGE(TBB)

include_directories(${TBB_INCLUDE_DIRS})
link_directories(${TBB_LIBRARY_DIRS})

bison_target(Parser parsepit.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc)
flex_target(Scanner scanpit.ll ${CMAKE_CURRENT_BINARY_DIR}/scaner.cc)

add_flex_bison_dependency(Scanner Parser)

add_executable(
            ../../prpa
            main.cc
            ${FLEX_Scanner_OUTPUTS}
            ${BISON_Parser_OUTPUTS}
            ${HH_FILES}
            ${SRC_FILES}
            ${HXX_FILES}
)


target_link_libraries(../../prpa filter)
TARGET_LINK_LIBRARIES(../../prpa ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(../../prpa ${TBB_LIBRARIES})
