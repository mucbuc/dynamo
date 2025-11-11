cmake_minimum_required(VERSION 3.27)
project(circuit)

add_library(circuit INTERFACE)

target_include_directories(circuit INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(circuit PROPERTIES
    CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	COMPILE_WARNING_AS_ERROR ON
)


