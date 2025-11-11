cmake_minimum_required(VERSION 3.27)

project(test_asserter VERSION 1.0.0 LANGUAGES CXX)
enable_testing()

add_executable(Example src/check_assert.cpp)
add_executable(Output src/check_test_output.cpp)

set_target_properties(Example PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR ON
)

set_target_properties(Output PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR ON
)

target_link_libraries(Example INTERFACE asserter)
target_link_libraries(Output INTERFACE asserter)

target_include_directories(Example SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(Output SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/lib)


add_test(
    NAME test_assert_failure
    COMMAND Example
)


