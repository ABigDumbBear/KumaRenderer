cmake_minimum_required(VERSION 3.10)
project(KumaGL VERSION 0.0.1)

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(assimp REQUIRED)
find_package(Freetype REQUIRED)

list(APPEND SOURCE_FILES
  src/3rd_party/glad/glad.c
  src/Font.cpp
  src/Mesh.cpp
  src/Model.cpp
  src/Shader.cpp
  src/Texture.cpp)

# Create the library.
add_library(KumaGL SHARED ${SOURCE_FILES})
target_include_directories(KumaGL PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/>
  ${ASSIMP_INCLUDE_DIRS}
  ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(KumaGL PUBLIC
  ${ASSIMP_LIBRARIES}
  ${FREETYPE_LIBRARIES})

install(TARGETS KumaGL
  EXPORT KumaGLTargets
  LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

install(EXPORT KumaGLTargets
  FILE KumaGLConfig.cmake
  NAMESPACE KumaGL::
  DESTINATION lib/cmake/KumaGL)

# Add extra build options.
option(BUILD_TESTS "Build the unit tests." OFF)
option(BUILD_EXAMPLES "Build the example applications." OFF)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
