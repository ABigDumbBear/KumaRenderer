# Find any third-party libraries.
find_package(glfw3 REQUIRED)

# Create the executable.
add_executable(lighting main.cpp)

# Link the executable with GLFW.
target_link_libraries(lighting PUBLIC glfw
                                      KumaGL)

# Install the executable and the resources.
install(TARGETS lighting DESTINATION ${EXAMPLES_INSTALL_DIR}/lighting)
install(DIRECTORY resources DESTINATION ${EXAMPLES_INSTALL_DIR}/lighting)
