# Find any third-party libraries.
find_package(glfw3 REQUIRED)

# Create the executable.
add_executable(cubes main.cpp)

# Link the executable with GLFW.
target_link_libraries(cubes PUBLIC glfw
                                   KumaGL)

# Install the executable and the resources.
install(TARGETS cubes DESTINATION ${EXAMPLES_INSTALL_DIR}/cubes)
install(DIRECTORY resources DESTINATION ${EXAMPLES_INSTALL_DIR}/cubes)
