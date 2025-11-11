cmake_minimum_required(VERSION 3.27)

project(Example)

add_subdirectory(lib/circuit)
add_subdirectory(lib/asserter)

add_executable(Example src/example.cpp)

target_link_libraries(Example PRIVATE asserter)
target_link_libraries(Example PRIVATE circuit)

set_target_properties(Example PROPERTIES
    CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	COMPILE_WARNING_AS_ERROR ON
)

if (EMSCRIPTEN)
    set_target_properties(Example PROPERTIES SUFFIX ".html")
    target_link_options(Example PRIVATE 
        --emrun
        -sASSERTIONS=1
    )
endif()

target_include_directories(Example SYSTEM PUBLIC ${CMAKE_SOURCE_DIR})


add_executable(Test src/main.cpp)

target_link_libraries(Test INTERFACE asserter)
target_link_libraries(Test PRIVATE circuit)

set_target_properties(Test PROPERTIES
    CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	COMPILE_WARNING_AS_ERROR ON
)

if (EMSCRIPTEN)
    set_target_properties(Test PROPERTIES SUFFIX ".html")
    target_link_options(Test PRIVATE 
        --emrun
        -sASSERTIONS=1
    )
endif()

target_include_directories(Test SYSTEM PUBLIC ${CMAKE_SOURCE_DIR})

