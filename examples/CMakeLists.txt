set(EXAMPLE_INSTALL_DIR bin/KumaGL/examples)

include(FetchContent)

FetchContent_Declare(
  glfw3
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.3.8
)

FetchContent_MakeAvailable(glfw3)

add_subdirectory(cubes)
#add_subdirectory(framebuffers)
#add_subdirectory(lighting)
#add_subdirectory(shadows)
