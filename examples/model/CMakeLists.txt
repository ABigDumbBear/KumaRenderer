find_package(glfw3 REQUIRED)

add_executable(model main.cpp)
target_link_libraries(model PUBLIC
  glfw
  KumaGL
)

install(TARGETS model
  EXPORT KumaGLTargets
  RUNTIME DESTINATION ${EXAMPLE_INSTALL_DIR}/model
)

install(DIRECTORY resources
  DESTINATION ${EXAMPLE_INSTALL_DIR}/model
)
