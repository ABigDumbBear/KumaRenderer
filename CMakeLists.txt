cmake_minimum_required(VERSION 3.10)
project(KumaRenderer VERSION 0.0.1)

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Gather up the source and header files.
set(SOURCE_FILES src/glad.c
                 src/Mesh.cpp
                 src/Shader.cpp
                 src/Texture.cpp)
set(HEADER_FILES include/glad/glad.h
                 include/KHR/khrplatform.h
                 include/Camera.hpp
                 include/Light.hpp
                 include/Mesh.hpp
                 include/Shader.hpp
                 include/Texture.hpp
                 include/Transform.hpp
                 include/Mat4.hpp
                 include/MathUtil.hpp
                 include/Vec3.hpp)

# Create the library.
add_library(KumaRenderer SHARED ${SOURCE_FILES})
target_include_directories(KumaRenderer PUBLIC include)

# Install the library and header files.
install(TARGETS KumaRenderer DESTINATION ${CMAKE_SOURCE_DIR}/install/lib)
install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/install/include)

# Add extra build options.
option(BUILD_TESTS "Build the unit tests." ON)
option(BUILD_EXAMPLES "Build the examples." ON)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
