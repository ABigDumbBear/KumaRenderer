add_executable(mathTest main.cpp)
target_link_libraries(mathTest PUBLIC KumaGL)

install(TARGETS mathTest DESTINATION tests)
