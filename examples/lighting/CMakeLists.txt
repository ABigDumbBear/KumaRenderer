find_package(glfw3 REQUIRED)

add_executable(lighting main.cpp)
target_link_libraries(lighting PUBLIC glfw KumaGL)

install(TARGETS lighting DESTINATION ${EXAMPLE_INSTALL_DIR}/lighting)
install(DIRECTORY resources DESTINATION ${EXAMPLE_INSTALL_DIR}/lighting)
