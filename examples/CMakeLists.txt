# Set a common install dir for all examples.
set(EXAMPLES_INSTALL_DIR ${CMAKE_SOURCE_DIR}/install/examples)

# Set the linker path to find the KumaGL library.
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${CMAKE_SOURCE_DIR}/install/lib")

# Add each example.
add_subdirectory(cubes)

if(TEXT_SUPPORT)
  add_subdirectory(text)
endif(TEXT_SUPPORT)
