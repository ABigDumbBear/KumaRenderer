# Create the executable.
add_executable(mathTest main.cpp)

# Include the header files.
target_include_directories(mathTest PUBLIC ${CMAKE_SOURCE_DIR}/include/math)

# Install the test executable.
install(TARGETS mathTest DESTINATION ${CMAKE_SOURCE_DIR}/install/tests)
