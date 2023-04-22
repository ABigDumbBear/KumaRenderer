# Find any third-party libraries.
find_package(glfw3 REQUIRED)

# Create the executable.
add_executable(model main.cpp)

# Link the executable with GLFW.
target_link_libraries(model PUBLIC glfw
                                   KumaGL)

# Include the header files.
target_include_directories(model PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Install the executable and the resources.
install(TARGETS model DESTINATION ${EXAMPLES_INSTALL_DIR}/model)
install(DIRECTORY resources DESTINATION ${EXAMPLES_INSTALL_DIR}/model)
