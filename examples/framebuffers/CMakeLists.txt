add_executable(framebuffers main.cpp)
target_link_libraries(framebuffers PUBLIC
  glfw
  KumaGL
)

install(TARGETS framebuffers
  EXPORT KumaGLTargets
  RUNTIME DESTINATION ${EXAMPLE_INSTALL_DIR}/framebuffers
)

install(DIRECTORY resources
  DESTINATION ${EXAMPLE_INSTALL_DIR}/framebuffers
)
