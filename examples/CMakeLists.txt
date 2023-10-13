set(EXAMPLE_INSTALL_DIR bin/KumaGL/examples)

# Retrieve the GLFW library, which is used by each example.
include(FetchContent)

FetchContent_Declare(
  glfw3
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.3.8
)

# Only build the GLFW library, not any of the extras.
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)

FetchContent_MakeAvailable(glfw3)

add_subdirectory(cubes)
add_subdirectory(framebuffers)
add_subdirectory(lighting)
add_subdirectory(shadows)
