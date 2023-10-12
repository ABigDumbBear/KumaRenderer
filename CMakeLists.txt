cmake_minimum_required(VERSION 3.10)
project(KumaGL
  VERSION 0.0.1
  LANGUAGES C CXX
)

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Only used by Windows; exports all public classes/functions
# automatically so manual __declspec calls aren't needed.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(src)

# Add extra build options.
option(BUILD_TESTS "Build the unit tests." ON)
option(BUILD_EXAMPLES "Build the example applications." ON)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
