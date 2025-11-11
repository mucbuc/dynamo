cmake_minimum_required(VERSION 3.15)

add_library(asserter INTERFACE
    src/archiver.hpp
    src/archiver.hxx
    src/asserter.hpp
    src/asserter.hxx
)

set_target_properties(asserter PROPERTIES
    CXX_STANDARD 11
)
