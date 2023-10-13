add_executable(shadows main.cpp)
target_link_libraries(shadows PUBLIC
  glfw
  KumaGL
)

install(TARGETS shadows
  EXPORT KumaGLTargets
  RUNTIME DESTINATION ${EXAMPLE_INSTALL_DIR}/shadows
)

install(DIRECTORY resources
  DESTINATION ${EXAMPLE_INSTALL_DIR}/shadows
)
