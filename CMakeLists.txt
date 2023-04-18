cmake_minimum_required(VERSION 3.10)
project(KumaRenderer VERSION 0.0.1)

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Gather up the source and header files for core features.
list(APPEND SOURCE_FILES
            src/core/glad.c
            src/core/Mesh.cpp
            src/core/Shader.cpp
            src/core/Texture.cpp)
list(APPEND HEADER_FILES
            include/3rd_party/KHR/khrplatform.h
            include/3rd_party/glad/glad.h
            include/3rd_party/stb_image/stb_image.h
            include/core/Mat4.hpp
            include/core/MathUtil.hpp
            include/core/Mesh.hpp
            include/core/Shader.hpp
            include/core/Texture.hpp
            include/core/Transform.hpp
            include/core/Vec3.hpp)
list(APPEND INCLUDE_DIRS
            include/3rd_party/
            include/core)

# Add optional features.
option(TEXT_SUPPORT "Adds support for loading font files." ON)
option(MODEL_SUPPORT "Adds support for loading model files." ON)

if(TEXT_SUPPORT)
  list(APPEND SOURCE_FILES src/text/Font.cpp)
  list(APPEND HEADER_FILES include/text/Font.hpp)
  list(APPEND INCLUDE_DIRS include/text)

  find_package(Freetype REQUIRED)
endif(TEXT_SUPPORT)

if(MODEL_SUPPORT)
  list(APPEND SOURCE_FILES src/model/Model.cpp)
  list(APPEND HEADER_FILES include/model/Model.hpp)
  list(APPEND INCLUDE_DIRS include/model)

  find_package(assimp REQUIRED)
endif(MODEL_SUPPORT)

# Create the library.
add_library(KumaRenderer SHARED ${SOURCE_FILES})
target_include_directories(KumaRenderer PUBLIC ${INCLUDE_DIRS})

if(TEXT_SUPPORT)
  target_link_libraries(KumaRenderer PUBLIC ${FREETYPE_LIBRARIES})
  target_include_directories(KumaRenderer PUBLIC ${FREETYPE_INCLUDE_DIRS})
endif(TEXT_SUPPORT)

if(MODEL_SUPPORT)
        target_link_libraries(KumaRenderer PUBLIC ${ASSIMP_LIBRARIES})
        target_include_directories(KumaRenderer PUBLIC ${ASSIMP_INCLUDE_DIRS})
endif(MODEL_SUPPORT)

# Install the library and header files.
install(TARGETS KumaRenderer DESTINATION ${CMAKE_SOURCE_DIR}/install/lib)
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
