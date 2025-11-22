cmake_minimum_required(VERSION 3.27)
project(dynamo)

add_library(dynamo INTERFACE)

set_target_properties(dynamo PROPERTIES
    CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	COMPILE_WARNING_AS_ERROR ON
)


