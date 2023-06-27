cmake_minimum_required(VERSION 3.10)
project(KumaGL VERSION 0.0.1)

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Gather up the source and header files for core features.
list(APPEND SOURCE_FILES
            src/3rd_party/glad/glad.c
            src/core/Mesh.cpp
            src/core/Shader.cpp
            src/core/Texture.cpp)
list(APPEND HEADER_FILES
            src/3rd_party/KHR/khrplatform.h
            src/3rd_party/glad/glad.h
            src/3rd_party/stb_image/stb_image.h
            src/core/Mesh.hpp
            src/core/Shader.hpp
            src/core/Texture.hpp
            src/core/Transform.hpp
            src/math/Mat4.hpp
            src/math/MathUtil.hpp
            src/math/Vec3.hpp)
list(APPEND INCLUDE_DIRS
            src/3rd_party
            src/core
            src/math)

# Add optional features.
option(TEXT_SUPPORT "Adds support for loading font files." ON)
option(MODEL_SUPPORT "Adds support for loading model files." ON)

if(TEXT_SUPPORT)
  list(APPEND SOURCE_FILES src/text/Font.cpp)
  list(APPEND HEADER_FILES src/text/Font.hpp)
  list(APPEND INCLUDE_DIRS src/text)

  find_package(Freetype REQUIRED)
endif(TEXT_SUPPORT)

if(MODEL_SUPPORT)
  list(APPEND SOURCE_FILES src/model/Model.cpp)
  list(APPEND HEADER_FILES src/model/Model.hpp)
  list(APPEND INCLUDE_DIRS src/model)

  find_package(assimp REQUIRED)
endif(MODEL_SUPPORT)

# Create the library.
add_library(KumaGL SHARED ${SOURCE_FILES})
target_include_directories(KumaGL PUBLIC ${INCLUDE_DIRS})

if(TEXT_SUPPORT)
  target_link_libraries(KumaGL PUBLIC ${FREETYPE_LIBRARIES})
  target_include_directories(KumaGL PUBLIC ${FREETYPE_INCLUDE_DIRS})
endif(TEXT_SUPPORT)

if(MODEL_SUPPORT)
  target_link_libraries(KumaGL PUBLIC ${ASSIMP_LIBRARIES})
  target_include_directories(KumaGL PUBLIC ${ASSIMP_INCLUDE_DIRS})
endif(MODEL_SUPPORT)

# Install the library and header files.
install(TARGETS KumaGL DESTINATION ${CMAKE_SOURCE_DIR}/install/lib)
install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/install/include)

# Add extra build options.
option(BUILD_TESTS "Build the unit tests." ON)
option(BUILD_EXAMPLES "Build the example applications." ON)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
