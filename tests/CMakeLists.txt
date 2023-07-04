# Create the executable.
add_executable(mathTest main.cpp)

# Include the header files.
target_include_directories(mathTest PUBLIC ${INCLUDE_DIR})
