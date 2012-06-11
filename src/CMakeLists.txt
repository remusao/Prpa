# Add subdirectories

#add_subdirectory(ast)

# Add the binary and sources
add_executable(
  ../../prpa
  main.cc
)

TARGET_LINK_LIBRARIES(../../prpa ${OpenCV_LIBS})
#target_link_libraries(../../../pit ast)
