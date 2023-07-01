cmake_minimum_required(VERSION 3.10)
project(KumaGL VERSION 0.0.1)

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# List the source files for core features.
list(APPEND SOURCE_FILES
            src/3rd_party/glad/glad.c
            src/core/Mesh.cpp
            src/core/Shader.cpp
            src/core/Texture.cpp)

# List the header files for core features.
list(APPEND HEADER_FILES
            src/core/Mesh.hpp
            src/core/Shader.hpp
            src/core/Texture.hpp
            src/math/Transform.hpp
            src/math/Mat4.hpp
            src/math/MathUtil.hpp
            src/math/Vec3.hpp)

# List the header files for third party code.
list(APPEND KHR_HEADERS src/3rd_party/KHR/khrplatform.h)
list(APPEND GLAD_HEADERS src/3rd_party/glad/glad.h)
list(APPEND STB_HEADERS src/3rd_party/stb/stb_image.h)

# List the directories to search for header files when compiling.
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

# Install the library and header files. All KumaGL headers go in the root
# include/KumaGL directory, while all third party headers go in their own folder
# inside of include/.
install(TARGETS KumaGL DESTINATION ${CMAKE_SOURCE_DIR}/install/lib)
install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/install/include/KumaGL)
install(FILES ${KHR_HEADERS} DESTINATION ${CMAKE_SOURCE_DIR}/install/include/KHR)
install(FILES ${GLAD_HEADERS} DESTINATION ${CMAKE_SOURCE_DIR}/install/include/glad)
install(FILES ${STB_HEADERS} DESTINATION ${CMAKE_SOURCE_DIR}/install/include/stb)

# Add extra build options.
option(BUILD_TESTS "Build the unit tests." ON)
option(BUILD_EXAMPLES "Build the example applications." ON)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
