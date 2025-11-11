project(asserter)

add_library(asserter INTERFACE
    src/archiver.hpp
    src/archiver.hxx
    src/asserter.hpp
    src/asserter.hxx
)

set_target_properties(asserter PROPERTIES
    CXX_STANDARD 11
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	COMPILE_WARNING_AS_ERROR ON
    LINKER_LANGUAGE CXX
)
