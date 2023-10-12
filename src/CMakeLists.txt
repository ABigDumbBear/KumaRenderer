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
  $<BUILD_INTERFACE:../include>
  $<BUILD_INTERFACE:../include/KumaGL>
  $<BUILD_INTERFACE:../external>
  $<INSTALL_INTERFACE:include/>
)

# Install the library and the include directory.
install(TARGETS KumaGL
  EXPORT KumaGLTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
)

install(EXPORT KumaGLTargets
  FILE KumaGLConfig.cmake
  NAMESPACE KumaGL::
  DESTINATION lib/cmake/KumaGL
)
