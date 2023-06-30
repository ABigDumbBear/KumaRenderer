# Find any third-party libraries.
find_package(glfw3 REQUIRED)

# Create the executable.
add_executable(text main.cpp)

# Link the executable with GLFW.
target_link_libraries(text PUBLIC glfw
                                  KumaGL)

# Install the executable and the resources.
install(TARGETS text DESTINATION ${EXAMPLES_INSTALL_DIR}/text)
install(DIRECTORY resources DESTINATION ${EXAMPLES_INSTALL_DIR}/text)
