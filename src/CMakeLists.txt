# Add subdirectories

add_subdirectory(filter)
add_subdirectory(interpreter)

# Add the binary and sources
add_executable(
  ../../prpa
  main.cc
)

TARGET_LINK_LIBRARIES(../../prpa ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(../../prpa filter)
TARGET_LINK_LIBRARIES(../../prpa interpreter)
#target_link_libraries(../../../pit ast)
