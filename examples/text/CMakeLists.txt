find_package(glfw3 REQUIRED)

add_executable(text main.cpp)
target_link_libraries(text PUBLIC
  glfw
  KumaGL
)

install(TARGETS text
  EXPORT KumaGLTargets
  RUNTIME DESTINATION ${EXAMPLE_INSTALL_DIR}/text
)

install(DIRECTORY resources
  DESTINATION ${EXAMPLE_INSTALL_DIR}/text
)
