find_package(glfw3 REQUIRED)

add_executable(cubes main.cpp)
target_link_libraries(cubes PUBLIC
  glfw
  KumaGL
)

install(TARGETS cubes
  EXPORT KumaGLTargets
  RUNTIME DESTINATION ${EXAMPLE_INSTALL_DIR}/cubes
)

install(DIRECTORY resources
  DESTINATION ${EXAMPLE_INSTALL_DIR}/cubes
)
