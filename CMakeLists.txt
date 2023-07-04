cmake_minimum_required(VERSION 3.10)
project(KumaGL VERSION 0.0.1)

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(assimp REQUIRED)
find_package(Freetype REQUIRED)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
list(APPEND SOURCE_FILES
            src/3rd_party/glad/glad.c
            src/Font.cpp
            src/Mesh.cpp
            src/Model.cpp
            src/Shader.cpp
            src/Texture.cpp)

# Create the library.
add_library(KumaGL SHARED ${SOURCE_FILES})
target_include_directories(KumaGL PUBLIC ${INCLUDE_DIR}
                                         ${ASSIMP_INCLUDE_DIRS}
                                         ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(KumaGL PUBLIC ${ASSIMP_LIBRARIES}
                                    ${FREETYPE_LIBRARIES})

# Add extra build options.
option(BUILD_TESTS "Build the unit tests." ON)
option(BUILD_EXAMPLES "Build the example applications." ON)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
