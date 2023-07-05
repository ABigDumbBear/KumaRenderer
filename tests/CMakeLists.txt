add_executable(mathTest main.cpp)
target_include_directories(mathTest PUBLIC ${INCLUDE_DIR})

install(TARGETS mathTest DESTINATION ${LOCAL_INSTALL_DIR}/tests)
