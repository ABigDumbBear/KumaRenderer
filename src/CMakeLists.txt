# Gather all the required source files.
list(APPEND KUMAGL_SOURCES
  glad/gl.c
  Framebuffer.cpp
  GLObject.cpp
  Mat4.cpp
  Mesh.cpp
  Renderbuffer.cpp
  Shader.cpp
  Texture.cpp
  VAO.cpp
  VBO.cpp
  Vec3.cpp
)

# Create the library.
add_library(KumaGL ${KUMAGL_SOURCES})
target_include_directories(KumaGL PUBLIC
  ../include/KumaGL
  ../external
)

# Install the library and the header files.
install(TARGETS KumaGL DESTINATION lib)
install(DIRECTORY ../include DESTINATION include)
